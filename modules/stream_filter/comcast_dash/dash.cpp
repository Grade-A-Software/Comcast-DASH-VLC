/*****************************************************************************
 * dash.cpp: DASH module
 *****************************************************************************
 * Copyright © 2010 - 2011 Klagenfurt University
 *
 * Created on: Aug 10, 2010
 * authors: christopher Mueller <christopher.mueller@itec.uni-klu.ac.at>
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
#include <errno.h>


<<<<<<< HEAD
#include "DASHManager.h"
#include "xml/DOMParser.h"
#include "xml/Node.h"
#include "mpd/MPD.h"
#include "mpd/MPDParser.h"
#include "mpd/MPDManager.h"
=======

using namespace comcast_dash;
using namespace comcast_dash::mpd;

>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b


using namespace dash;
using namespace dash::mpd;
using namespace dash::xml;
using namespace dash::http;
using namespace dash::buffer;
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
<<<<<<< HEAD
        set_shortname( N_("DASH"))
        set_description( N_("Dynamic Adaptive Streaming over HTTP") )
        set_capability( "stream_filter", 19 )
        set_category( CAT_INPUT )
        set_subcategory( SUBCAT_INPUT_STREAM_FILTER )
        add_integer( "dash-prefwidth",  480, DASH_WIDTH_TEXT,  DASH_WIDTH_LONGTEXT,  true )
        add_integer( "dash-prefheight", 360, DASH_HEIGHT_TEXT, DASH_HEIGHT_LONGTEXT, true )
        add_integer( "dash-buffersize", 30, DASH_BUFFER_TEXT, DASH_BUFFER_LONGTEXT, true )
        set_callbacks( Open, Close )
=======
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
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
vlc_module_end ()

/*****************************************************************************
 * Local prototypes
 *****************************************************************************/
struct stream_sys_t
{
<<<<<<< HEAD
        DASHManager   *p_dashManager;
        mpd::MPD      *p_mpd;
        uint64_t                            position;
        bool                                isLive;
=======
    uint64_t                            position;
    bool                                isLive;
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
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
<<<<<<< HEAD

    if(!xml::DOMParser::isDash(p_stream->p_source))
        return VLC_EGENERIC;

    //Build a XML tree
    xml::DOMParser        parser(p_stream->p_source);
=======
    if(!comcast_dash::xml::DOMParser::isDash(p_stream->p_source))
        return VLC_EGENERIC;
    else
        msg_Info(p_stream,"Is DASH!");
    
    //Build a XML tree
    comcast_dash::xml::DOMParser        parser(p_stream->p_source);
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
    if( !parser.parse() )
    {
        msg_Dbg( p_stream, "Could not parse mpd file." );
        return VLC_EGENERIC;
<<<<<<< HEAD
    }

    //Begin the actual MPD parsing:

    //    dash::mpd::MPDParser *mpdParser = new dash::mpd::MPDParser(parser.getRootNode(), p_stream->p_source);
    //dash::mpd::MPD *mpd = mpdParser->getMPD();
    mpd::MPDManager *mpdManager = new mpd::MPDManager(parser.getRootNode(), p_stream);
    if(mpdManager->mpd == NULL)
        return VLC_EGENERIC;
=======
    }
    else {
        //      parser.print();
        Parser * dashParser = new Parser(parser.getRootNode(),p_stream);
        MPD *mpd = dashParser->parse();
        
        std::vector<std::string> urls = mpd->getURLs();
        
        for (size_t i = 0; i < urls.size(); i++) {
            
            msg_Info(p_stream,urls.at(i).c_str());
        }
    }
    
    
    
    
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
    
    stream_sys_t        *p_sys = (stream_sys_t *) malloc(sizeof(stream_sys_t));
    if (unlikely(p_sys == NULL))
        return VLC_ENOMEM;
<<<<<<< HEAD

    p_sys->p_mpd = mpdManager->mpd;
    DASHManager *p_dashManager = new DASHManager(mpdManager, p_stream->p_source);

    if(!p_dashManager->start())
    {
        delete p_dashManager;
        free( p_sys );
        return VLC_EGENERIC;
    }
    p_sys->p_dashManager    = p_dashManager;
=======
    
    
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
    p_sys->position         = 0;
    p_sys->isLive           = p_dashManager->getMpdManager()->getMPD()->isLive();
    p_stream->p_sys         = p_sys;
    p_stream->pf_read       = Read;
    p_stream->pf_peek       = Peek;
    p_stream->pf_control    = Control;
<<<<<<< HEAD

    msg_Dbg(p_obj,"opening mpd file (%s)", p_stream->psz_path);

=======
    
    
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
    return VLC_SUCCESS;
}
/*****************************************************************************
 * Close:
 *****************************************************************************/
static void Close(vlc_object_t *p_obj)
{
    stream_t                            *p_stream       = (stream_t*) p_obj;
    stream_sys_t                        *p_sys          = (stream_sys_t *) p_stream->p_sys;
<<<<<<< HEAD
    dash::DASHManager                   *p_dashManager  = p_sys->p_dashManager;

    delete(p_dashManager);
=======
    
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
    free(p_sys);
}
/*****************************************************************************
 * Callbacks:
 *****************************************************************************/
static int  Seek            ( stream_t *p_stream, uint64_t pos )
{
    stream_sys_t        *p_sys          = (stream_sys_t *) p_stream->p_sys;
<<<<<<< HEAD
    dash::DASHManager   *p_dashManager  = p_sys->p_dashManager;
    int                 i_ret           = 0;
    unsigned            i_len           = 0;
    long                i_read          = 0;

    if( pos < p_sys->position )
    {
        if( p_sys->position - pos > UINT_MAX )
        {
            msg_Err( p_stream, "Cannot seek backward that far!" );
            return VLC_EGENERIC;
        }
        i_len = p_sys->position - pos;
        i_ret = p_dashManager->seekBackwards( i_len );
        if( i_ret == VLC_EGENERIC )
        {
            msg_Err( p_stream, "Cannot seek backward outside the current block :-/" );
            return VLC_EGENERIC;
        }
        else
            return VLC_SUCCESS;
    }

    /* Seek forward */
    if( pos - p_sys->position > UINT_MAX )
    {
        msg_Err( p_stream, "Cannot seek forward that far!" );
        return VLC_EGENERIC;
    }
    i_len = pos - p_sys->position;
    i_read = Read( p_stream, (void *)NULL, i_len );
    if( (unsigned)i_read == i_len )
        return VLC_SUCCESS;
    else
        return VLC_EGENERIC;
=======
    
    int                 i_ret           = 0;
    unsigned            i_len           = 0;
    long                i_read          = 0;
    
    
    return VLC_SUCCESS;
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
}

static int  Read            (stream_t *p_stream, void *p_ptr, unsigned int i_len)
{
    stream_sys_t        *p_sys          = (stream_sys_t *) p_stream->p_sys;
    dash::DASHManager   *p_dashManager  = p_sys->p_dashManager;
    uint8_t             *p_buffer       = (uint8_t*)p_ptr;
    int                 i_ret           = 0;
    int                 i_read          = 0;
<<<<<<< HEAD

    while( i_len > 0 )
    {
        i_read = p_dashManager->read( p_buffer, i_len );
        if( i_read < 0 )
            break;
        p_buffer += i_read;
        i_ret += i_read;
        i_len -= i_read;
    }
    p_buffer -= i_ret;

    if (i_read < 0)
    {
        switch (errno)
        {
            case EINTR:
            case EAGAIN:
                break;
            default:
                msg_Dbg(p_stream, "DASH Read: failed to read (%s)",
                        vlc_strerror_c(errno));
                return 0;
        }
        return 0;
    }

    p_sys->position += i_ret;

    return i_ret;
=======
    
    
    return VLC_SUCCESS;
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
}

static int  Peek            (stream_t *p_stream, const uint8_t **pp_peek, unsigned int i_peek)
{
    stream_sys_t        *p_sys          = (stream_sys_t *) p_stream->p_sys;
    dash::DASHManager   *p_dashManager  = p_sys->p_dashManager;

    return p_dashManager->peek( pp_peek, i_peek );
}

static int  Control         (stream_t *p_stream, int i_query, va_list args)
{
    stream_sys_t *p_sys = p_stream->p_sys;
<<<<<<< HEAD

    switch (i_query)
    {
        case STREAM_CAN_SEEK:
        case STREAM_CAN_FASTSEEK:
            /*TODO Support Seek */
            *(va_arg (args, bool *)) = SEEK;
            break;
        case STREAM_CAN_PAUSE:
        case STREAM_CAN_CONTROL_PACE:
            *(va_arg (args, bool *)) = false; /* TODO */
            break;

        case STREAM_GET_POSITION:
            *(va_arg (args, uint64_t *)) = p_sys->position;
            break;
        case STREAM_SET_POSITION:
        {
            uint64_t pos = (uint64_t)va_arg(args, uint64_t);
            if(Seek(p_stream, pos) == VLC_SUCCESS)
            {
                p_sys->position = pos;
                break;
            }
            else
                return VLC_EGENERIC;
        }
        case STREAM_GET_SIZE:
        {
            uint64_t*   res = (va_arg (args, uint64_t *));
            if(p_sys->isLive)
                *res = 0;
            else
            {
	      const dash::mpd::Representation *rep = p_sys->p_dashManager->getCurrentRepresentation();
                if ( rep == NULL )
                    *res = 0;
                else
                    *res = p_sys->p_mpd->getDuration() * rep->getBandwidth() / 8;
            }
            break;
        }
        case STREAM_GET_PTS_DELAY:
            *va_arg (args, int64_t *) =
                var_InheritInteger(p_stream, "network-caching");
             break;

    default:
      return VLC_EGENERIC;
    }
=======
    
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
    return VLC_SUCCESS;
}
