/*****************************************************************************
 * dash.cpp: DASH module
 *****************************************************************************
 * Copyright © 2010 - 2011 Klagenfurt University
 *
 * Created on: Aug 10, 2010
 * Authors: Christopher Mueller <christopher.mueller@itec.uni-klu.ac.at>
 *          Christian Timmerer  <christian.timmerer@itec.uni-klu.ac.at>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/*****************************************************************************
 * Preamble
 *****************************************************************************/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_stream.h>
#include "xml/DOMParser.h"
#include <errno.h>



using namespace dash;



#define SEEK 0

/*****************************************************************************
 * Module descriptor
 *****************************************************************************/
static int  Open    (vlc_object_t *);
static void Close   (vlc_object_t *);

#define DASH_WIDTH_TEXT N_("Preferred Width")
#define DASH_WIDTH_LONGTEXT N_("Preferred Width")

#define DASH_HEIGHT_TEXT N_("Preferred Height")
#define DASH_HEIGHT_LONGTEXT N_("Preferred Height")

#define DASH_BUFFER_TEXT N_("Buffer Size (Seconds)")
#define DASH_BUFFER_LONGTEXT N_("Buffer size in seconds")

vlc_module_begin ()
        set_shortname( N_("DASH"))
        set_description( N_("Dynamic Adaptive Streaming over HTTP") )
        set_capability( "stream_filter", 19 )
        set_category( CAT_INPUT )
        set_subcategory( SUBCAT_INPUT_STREAM_FILTER )
        add_integer( "dash-prefwidth",  480, DASH_WIDTH_TEXT,  DASH_WIDTH_LONGTEXT,  true )
        add_integer( "dash-prefheight", 360, DASH_HEIGHT_TEXT, DASH_HEIGHT_LONGTEXT, true )
        add_integer( "dash-buffersize", 30, DASH_BUFFER_TEXT, DASH_BUFFER_LONGTEXT, true )
        add_string( "dash-url", "", "URL", "URL of the XML file", false);
        set_callbacks( Open, Close )
vlc_module_end ()

/*****************************************************************************
 * Local prototypes
 *****************************************************************************/
struct stream_sys_t
{
        uint64_t                            position;
        bool                                isLive;
};

static int  Read            (stream_t *p_stream, void *p_ptr, unsigned int i_len);
static int  Peek            (stream_t *p_stream, const uint8_t **pp_peek, unsigned int i_peek);
static int  Control         (stream_t *p_stream, int i_query, va_list args);

/*****************************************************************************
 * Open:
 *****************************************************************************/
static int Open(vlc_object_t *p_obj)
{
    stream_t *p_stream = (stream_t*) p_obj;
    if(!dash::xml::DOMParser::isDash(p_stream->p_source))
      return VLC_EGENERIC;
    else
      msg_Info(p_stream,"Is DASH!");

    //Build a XML tree                                                                                  
    dash::xml::DOMParser        parser(p_stream->p_source);
    if( !parser.parse() )
      {
        msg_Dbg( p_stream, "Could not parse mpd file." );
        return VLC_EGENERIC;
      }
    else {
      parser.print();
    }

    
    stream_sys_t        *p_sys = (stream_sys_t *) malloc(sizeof(stream_sys_t));
    if (unlikely(p_sys == NULL))
        return VLC_ENOMEM;

    
    p_sys->position         = 0;
    p_sys->isLive           = true;
    p_stream->p_sys         = p_sys;
    p_stream->pf_read       = Read;
    p_stream->pf_peek       = Peek;
    p_stream->pf_control    = Control;


    return VLC_SUCCESS;
}
/*****************************************************************************
 * Close:
 *****************************************************************************/
static void Close(vlc_object_t *p_obj)
{
    stream_t                            *p_stream       = (stream_t*) p_obj;
    stream_sys_t                        *p_sys          = (stream_sys_t *) p_stream->p_sys;
 
    free(p_sys);
}
/*****************************************************************************
 * Callbacks:
 *****************************************************************************/
static int  Seek            ( stream_t *p_stream, uint64_t pos )
{
    stream_sys_t        *p_sys          = (stream_sys_t *) p_stream->p_sys;

    int                 i_ret           = 0;
    unsigned            i_len           = 0;
    long                i_read          = 0;
    

    return VLC_SUCCESS;
}

static int  Read            (stream_t *p_stream, void *p_ptr, unsigned int i_len)
{
    stream_sys_t        *p_sys          = (stream_sys_t *) p_stream->p_sys;
    uint8_t             *p_buffer       = (uint8_t*)p_ptr;
    int                 i_ret           = 0;
    int                 i_read          = 0;

    
    return VLC_SUCCESS;
}

static int  Peek            (stream_t *p_stream, const uint8_t **pp_peek, unsigned int i_peek)
{
    stream_sys_t        *p_sys          = (stream_sys_t *) p_stream->p_sys;
    return 0;
}

static int  Control         (stream_t *p_stream, int i_query, va_list args)
{
    stream_sys_t *p_sys = p_stream->p_sys;

    return VLC_SUCCESS;
}
