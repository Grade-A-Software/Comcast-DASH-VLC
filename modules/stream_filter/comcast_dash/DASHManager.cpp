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

using namespace dash;


DASHManager::DASHManager    ( mpd::MPDManager *manager, stream_t *stream) :
             conManager     ( NULL ),
             currentChunk   ( NULL ),
             mpdManager     ( manager ),
             mpd            ( NULL ),
             stream         ( stream ),
             downloader     ( NULL ),
             buffer         ( NULL )
{
  this->mpd = null; //manager->mpd;
}
DASHManager::~DASHManager   ()
{
    delete this->downloader;
    delete this->buffer;
    delete this->conManager;
    delete this->mpdManager;
}

bool    DASHManager::start()
{

  if ( this->mpdManager == NULL )
    return false;
  
  
  this->conManager = new http::HTTPConnectionManager(this->mpdManager, this->stream);
  this->buffer     = new buffer::BlockBuffer(this->stream);
  this->downloader = new DASHDownloader(this->conManager, this->buffer);
  
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

const Chunk *DASHManager::getCurrentChunk() const
{
    return this->currentChunk;
}

dash::mpd::Representation DASHManager::getCurrentRepresentation() {
  return this->mpdManager->getCurrentRepresentation();
}
