/*
 * MPD.h
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

#ifndef MPD_H_
#define MPD_H_

#include <vector>
#include <string>
#include <map>
#include <vlc_common.h>
#include <vlc_arrays.h>
#include <sstream>

#include "Period.h"
#include "mpd/Representation.h"
#include "mpd/Segment.h"
#include "mpd/AdaptationSet.h"
#include "http/Chunk.h"

namespace comcast_dash
{
    namespace mpd
    {
        class MPD
        {
        public:
            MPD();
            virtual ~MPD();
            
            const std::vector<Period *>& getPeriods() const;
            
            void addPeriod(Period *period);
            
            std::vector<std::string> getURLs();
            http::Chunk * getNextChunk();
            std::vector<std::string> getTimeLineURLs();
            int getDuration() const;
            Representation* getWorstRepresentation();
        private:
	    int duration;
            std::vector<Period *> periods;
            uint64_t count;
            std::vector<std::string> schedule;
        };
    }
}
#endif /* MPD_H_ */
