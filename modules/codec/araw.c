/*****************************************************************************
 * araw.c: Pseudo audio decoder; for raw pcm data
 *****************************************************************************
 * Copyright (C) 2001, 2002 VideoLAN
 * $Id: araw.c,v 1.1 2002/10/14 21:59:44 fenrir Exp $
 *
 * Authors: Laurent Aimar <fenrir@via.ecp.fr>
 *      
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/*****************************************************************************
 * Preamble
 *****************************************************************************/
#include <vlc/vlc.h>
#include <vlc/aout.h>
#include <vlc/decoder.h>
#include <vlc/input.h>

#include <stdlib.h>                                      /* malloc(), free() */
#include <string.h>                                              /* strdup() */

/*****************************************************************************
 * Local prototypes
 *****************************************************************************/
typedef struct waveformatex_s
{
    u16 i_formattag;
    u16 i_channels;
    u32 i_samplespersec;
    u32 i_avgbytespersec;
    u16 i_blockalign;
    u16 i_bitspersample;
    u16 i_size; /* the extra size in bytes */
    u8  *p_data; /* The extra data */
} waveformatex_t;

typedef struct adec_thread_s
{
    waveformatex_t  format;

    /* The bit stream structure handles the PES stream at the bit level */
    bit_stream_t        bit_stream;

    /* Input properties */
    decoder_fifo_t *p_fifo;
    
    /* Output properties */
    aout_instance_t *   p_aout;       /* opaque */
    aout_input_t *      p_aout_input; /* opaque */
    audio_sample_format_t output_format;

    audio_date_t        date;
    mtime_t             pts;

} adec_thread_t;

static int  OpenDecoder    ( vlc_object_t * );

static int  RunDecoder     ( decoder_fifo_t * );
static int  InitThread     ( adec_thread_t * );
static void DecodeThread   ( adec_thread_t * );
static void EndThread      ( adec_thread_t * );

/*****************************************************************************
 * Module descriptor
 *****************************************************************************/

vlc_module_begin();
    set_description( _("Pseudo Raw Audio decoder") );
    set_capability( "decoder", 50 );
    set_callbacks( OpenDecoder, NULL );
vlc_module_end();

/*****************************************************************************
 * OpenDecoder: probe the decoder and return score
 *****************************************************************************
 * Tries to launch a decoder and return score so that the interface is able
 * to choose.
 *****************************************************************************/
static int OpenDecoder( vlc_object_t *p_this )
{
    decoder_fifo_t *p_fifo = (decoder_fifo_t*) p_this;
    
    switch( p_fifo->i_fourcc )
    {   
        case VLC_FOURCC('a','r','a','w'):
        case VLC_FOURCC('t','w','o','s'): /* for mov file */
            p_fifo->pf_run = RunDecoder;
            return VLC_SUCCESS;
            
        default:
            return VLC_EGENERIC;
    }

}

/*****************************************************************************
 * RunDecoder: this function is called just after the thread is created
 *****************************************************************************/
static int RunDecoder( decoder_fifo_t *p_fifo )
{
    adec_thread_t *p_adec;
    int b_error;

    if( !( p_adec = malloc( sizeof( adec_thread_t ) ) ) )
    {
        msg_Err( p_fifo, "out of memory" );
        DecoderError( p_fifo );
        return( -1 );
    }
    memset( p_adec, 0, sizeof( adec_thread_t ) );
    
    p_adec->p_fifo = p_fifo;

    if( InitThread( p_adec ) != 0 )
    {
        DecoderError( p_fifo );
        return( -1 );
    }

    while( ( !p_adec->p_fifo->b_die )&&( !p_adec->p_fifo->b_error ) )
    {
        DecodeThread( p_adec );
    }


    if( ( b_error = p_adec->p_fifo->b_error ) )
    {
        DecoderError( p_adec->p_fifo );
    }

    EndThread( p_adec );
    if( b_error )
    {
        return( -1 );
    }

    return( 0 );
}


#define FREE( p ) if( p ) free( p ); p = NULL
#define GetWLE( p ) \
    ( *(u8*)(p) + ( *((u8*)(p)+1) << 8 ) )

#define GetDWLE( p ) \
    (  *(u8*)(p) + ( *((u8*)(p)+1) << 8 ) + \
        ( *((u8*)(p)+2) << 16 ) + ( *((u8*)(p)+3) << 24 ) )
    
static void GetWaveFormatEx( waveformatex_t *p_wh,
                             u8 *p_data )
{

    p_wh->i_formattag     = GetWLE( p_data );
    p_wh->i_channels      = GetWLE( p_data + 2 );
    p_wh->i_samplespersec = GetDWLE( p_data + 4 );
    p_wh->i_avgbytespersec= GetDWLE( p_data + 8 );
    p_wh->i_blockalign    = GetWLE( p_data + 12 );
    p_wh->i_bitspersample = GetWLE( p_data + 14 );
    if( p_wh->i_formattag != 1 )
    {
        p_wh->i_size          = GetWLE( p_data + 16 );

        if( p_wh->i_size )
        {
            p_wh->p_data = malloc( p_wh->i_size );
            memcpy( p_wh->p_data, p_data + 18, p_wh->i_size );
        }
    }
}

/* get the first pes from fifo */
static pes_packet_t *PESGetFirst( decoder_fifo_t *p_fifo )
{
    pes_packet_t *p_pes;

    vlc_mutex_lock( &p_fifo->data_lock );

    /* if fifo is empty wait */ 
    while( !p_fifo->p_first )
    {
        if( p_fifo->b_die )
        {
            vlc_mutex_unlock( &p_fifo->data_lock );
            return NULL;
        }
        vlc_cond_wait( &p_fifo->data_wait, &p_fifo->data_lock );
    }
    p_pes = p_fifo->p_first;

    vlc_mutex_unlock( &p_fifo->data_lock );

    return p_pes;
}
static int PESGetSize( pes_packet_t *p_pes )
{
    data_packet_t *p_data;
    int i_size = 0;

    if( !p_pes )
    {
        return( 0 );
    }

    for( p_data = p_pes->p_first; p_data != NULL; p_data = p_data->p_next )
    {
        i_size += p_data->p_payload_end - p_data->p_payload_start;
    }

    return( i_size );
}

/*****************************************************************************
 * InitThread: initialize data before entering main loop
 *****************************************************************************/
static int InitThread( adec_thread_t * p_adec )
{

    if( p_adec->p_fifo->p_demux_data )
    {
        GetWaveFormatEx( &p_adec->format,
                         (u8*)p_adec->p_fifo->p_demux_data );
        /* fixing some values */
        if( p_adec->format.i_formattag == 1 && !p_adec->format.i_blockalign )
        {
            p_adec->format.i_blockalign = p_adec->format.i_channels * 
                    ( ( p_adec->format.i_bitspersample + 7 ) / 8 );
        }
    }
    else
    {
        msg_Err( p_adec->p_fifo, "unknown raw format" );
        return( -1 );
    }

    msg_Dbg( p_adec->p_fifo,
             "raw format: samplerate:%dHz channels:%d bits/sample:%d blockalign:%d",
             p_adec->format.i_samplespersec,
             p_adec->format.i_channels,
             p_adec->format.i_bitspersample, p_adec->format.i_blockalign );

    /* Initialize the thread properties */
    switch( ( p_adec->format.i_bitspersample + 7 ) / 8 )
    {
        case( 2 ):
            p_adec->output_format.i_format = VLC_FOURCC('s','1','6','l');
            break;
        case( 3 ):
            p_adec->output_format.i_format = VLC_FOURCC('s','2','4','l');
            break;
        case( 4 ):
            p_adec->output_format.i_format = VLC_FOURCC('s','3','2','l');
            break;

        case( 1 ):
        default:
            msg_Err( p_adec->p_fifo, "bad parameters(bits/sample)" );
            return( -1 );
    }
    p_adec->output_format.i_rate = p_adec->format.i_samplespersec;
    p_adec->output_format.i_channels = p_adec->format.i_channels;
    p_adec->p_aout = NULL;
    p_adec->p_aout_input = NULL;

    /* **** Create a new audio output **** */
    aout_DateInit( &p_adec->date, p_adec->output_format.i_rate );
    p_adec->p_aout_input = aout_DecNew( p_adec->p_fifo,
                                        &p_adec->p_aout,
                                        &p_adec->output_format );
    if( !p_adec->p_aout_input )
    {
        msg_Err( p_adec->p_fifo, "cannot create aout" );
        return( -1 );
    }

    /* Init the BitStream */
    InitBitstream( &p_adec->bit_stream, p_adec->p_fifo,
                   NULL, NULL );

    return( 0 );
}

/*****************************************************************************
 * DecodeThread: decodes a frame
 *****************************************************************************/
static void DecodeThread( adec_thread_t *p_adec )
{
    aout_buffer_t   *p_aout_buffer;
    int             i_samples; // per channels
    int             i_size;
    pes_packet_t    *p_pes;

    /* **** get samples count **** */
    p_pes = PESGetFirst( p_adec->p_fifo );
    
    i_size = PESGetSize( p_pes );
    if( p_adec->format.i_blockalign > 0 )
    {
        i_size -= i_size % p_adec->format.i_blockalign;
    }
    i_size = __MAX( i_size, p_adec->format.i_blockalign );

    if( !i_size || !p_pes )
    {
        msg_Err( p_adec->p_fifo, "infinite loop..." );
        return;
    }
    i_samples = i_size / 
                ( ( p_adec->format.i_bitspersample + 7 ) / 8 ) / 
                p_adec->format.i_channels;

//    msg_Warn( p_adec->p_fifo, "got %d samples (%d bytes)", i_samples, i_size );
    p_adec->pts = p_pes->i_pts;
        
    /* **** Now we can output these samples **** */
    
    if( p_adec->pts != 0 && p_adec->pts != aout_DateGet( &p_adec->date ) )
    {
        aout_DateSet( &p_adec->date, p_adec->pts );
    }
    else if( !aout_DateGet( &p_adec->date ) )
    {
        return;
    }

    p_aout_buffer = aout_DecNewBuffer( p_adec->p_aout, 
                                       p_adec->p_aout_input,
                                       i_samples );
    if( !p_aout_buffer )
    {
        msg_Err( p_adec->p_fifo, "cannot get aout buffer" );
        p_adec->p_fifo->b_error = 1;
        return;
    }
    
    p_aout_buffer->start_date = aout_DateGet( &p_adec->date );
    p_aout_buffer->end_date = aout_DateIncrement( &p_adec->date,
                                                  i_samples );
    GetChunk( &p_adec->bit_stream,
              p_aout_buffer->p_buffer,
              p_aout_buffer->i_nb_bytes );

    aout_DecPlay( p_adec->p_aout, p_adec->p_aout_input, p_aout_buffer );
}


/*****************************************************************************
 * EndThread : faad decoder thread destruction
 *****************************************************************************/
static void EndThread (adec_thread_t *p_adec)
{
    if( p_adec->p_aout_input )
    {
        aout_DecDelete( p_adec->p_aout, p_adec->p_aout_input );
    }

    FREE( p_adec->format.p_data );

    msg_Dbg( p_adec->p_fifo, "raw audio decoder closed" );
        
    free( p_adec );
}


