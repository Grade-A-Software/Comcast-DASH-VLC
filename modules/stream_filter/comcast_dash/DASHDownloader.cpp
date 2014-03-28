/*
 * DASHDownloader.h
 *****************************************************************************
 * Copyright (C) 2010 - 2011 Klagenfurt University
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

#include "DASHDownloader.h"

using namespace comcast_dash;
using namespace comcast_dash::http;
using namespace comcast_dash::logic;
using namespace comcast_dash::buffer;


DASHDownloader::DASHDownloader  (HTTPConnectionManager *conManager, BlockBuffer *buffer, stream_t *stream) : stream(stream)
{
    this->t_sys                     = (thread_sys_t *) malloc(sizeof(thread_sys_t));
    this->t_sys->conManager         = conManager;
    this->t_sys->buffer             = buffer;
    this->t_sys->stream = stream;

}
DASHDownloader::~DASHDownloader ()
{
    this->t_sys->buffer->setEOF(true);
    vlc_join(this->dashDLThread, NULL);
    free(this->t_sys);
}

/*bool        DASHDownloader::start       ()
{
  msg_Info(this->stream, "Starting DOWNLOAD");
  vlc_join(this->dashDLThread, NULL);
  if(vlc_clone(&(this->dashDLThread), download, (void*)this->t_sys, VLC_THREAD_PRIORITY_LOW))
    return false;

    return true;
    }*/

void*       DASHDownloader::download    (void *thread_sys)
{
}

bool DASHDownloader::start() {
  thread_sys_t            *t_sys              = this->t_sys;;
    HTTPConnectionManager   *conManager         = t_sys->conManager;
    BlockBuffer             *buffer             = t_sys->buffer;
    block_t                 *block              = block_Alloc(BLOCKSIZE);
    stream_t *stream = t_sys->stream;
    int                     ret                 = 0;

    int i = 0;
    do {
      
      msg_Info(stream,"READING");
      std::stringstream ss;
      ss<<net_ConnectTCP(stream,"nh.lab.xcal.tv",80) << " :)";
      msg_Info(stream,ss.str().c_str());
        ret = conManager->read(block);
	std::stringstream ss2;
	ss2<<ret<<" bytes returned!!!!!!";
	msg_Info(stream,ss2.str().c_str());
        if(ret > 0)
        {
            block_t *bufBlock = block_Alloc(ret);
            memcpy(bufBlock->p_buffer, block->p_buffer, ret);

            bufBlock->i_length = block->i_length;
            buffer->put(bufBlock);
        }
        i++;
    }while(i<5);
    buffer->setEOF(true);
    block_Release(block);

    return true;
}
