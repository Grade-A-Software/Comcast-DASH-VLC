/*****************************************************************************
 * DASHManager.cpp
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
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "DASHManager.h"

using namespace comcast_dash;
using namespace comcast_dash::http;
using namespace comcast_dash::xml;
using namespace comcast_dash::logic;
using namespace comcast_dash::mpd;
using namespace comcast_dash::buffer;

DASHManager::DASHManager   ( MPD *mpd,
                         /*     IAdaptationLogic::LogicType type,*/
				 stream_t *stream) :
             conManager     ( NULL ),
             currentChunk   ( NULL ),
            // adaptationLogic( NULL ),
             //logicType      ( type ),
//             mpdManager     ( NULL ),
             mpd            ( mpd ),
             stream         ( stream ),
             downloader     ( NULL ),
             buffer         ( NULL )
{
}
DASHManager::~DASHManager   ()
{
    delete this->downloader;
    delete this->buffer;
    delete this->conManager;
  //  delete this->adaptationLogic;
//    delete this->mpdManager;
}

bool    DASHManager::start()
{
    if ( this->mpd == NULL )
        return false;

<<<<<<< HEAD
    this->conManager = new comcast_dash::http::HTTPConnectionManager(this->mpd,this->stream);
    this->buffer     = new BlockBuffer(this->stream);
    this->downloader = new DASHDownloader(this->conManager, this->buffer);
=======
   /* this->adaptationLogic = AdaptationLogicFactory::create( this->logicType, this->mpdManager, this->stream);

    if ( this->adaptationLogic == NULL )
        return false;
*/
    std::stringstream ss;
    ss << this->mpd->getTimeLineURLs().size();
    msg_Info(this->stream,ss.str().c_str());
    this->conManager = new comcast_dash::http::HTTPConnectionManager(
				this->mpd,
						 this->stream);
    this->buffer     = new BlockBuffer(this->stream);
    this->downloader = new DASHDownloader(this->conManager, this->buffer, this->stream);
    
   // this->conManager->attach(this->adaptationLogic);
   // this->buffer->attach(this->adaptationLogic);
>>>>>>> dash_manager

    return this->downloader->start();
}

int     DASHManager::read( void *p_buffer, size_t len )
{
    return this->buffer->get(p_buffer, len);
}

int     DASHManager::seekBackwards( unsigned i_len )
{
    return this->buffer->seekBackwards( i_len );
}

int     DASHManager::peek( const uint8_t **pp_peek, size_t i_peek )
{
    return this->buffer->peek(pp_peek, i_peek);
}

//const mpd::IMPDManager*         DASHManager::getMpdManager() const
//{
//    return this->mpdManager;
//}
/*
const logic::IAdaptationLogic*  DASHManager::getAdaptionLogic() const
{
    return this->adaptationLogic;
}
*/
const Chunk *DASHManager::getCurrentChunk() const
{
    return this->currentChunk;
}
