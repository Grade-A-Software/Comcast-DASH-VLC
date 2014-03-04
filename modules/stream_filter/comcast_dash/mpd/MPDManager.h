/*
 * MPDManager.h
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Jan 27, 2010
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

#ifndef MPDMANAGER_H_
#define MPDMANAGER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "MPD.h"
#include "Period.h"
#include "AdaptationSet.h"
#include "Representation.h"
#include "MPDParser.h"
#include "Segment.h"


namespace dash
{
    namespace mpd
    {
        class MPDManager
        {
            public:
	        MPDManager            (Node * root,stream_t * p_stream);
                virtual ~MPDManager   ();
		

                virtual const std::vector<Period *>&    getPeriods              () const;
                virtual Period*                         getFirstPeriod          ();
                virtual Period*                         getNextPeriod           (Period *period);
                virtual Representation*                 getBestRepresentation   (Period *period);
                virtual const std::vector<Segment *>          getSegments             (const Representation *rep);
		virtual  Representation*                 getRepresentation       (Period *period, uint64_t bitrate) const;
                virtual const MPD*                      getMPD                  () const;
                virtual Representation*                 getRepresentation       (Period *period, uint64_t bitrate,
                                                                         int width, int height) const;
		virtual dash::http::Chunk* getNextChunk();
                virtual const mpd::Representation *getCurrentRepresentation() const;
                MPD *mpd;
		
		size_t count;
		std::vector<Segment *> schedule;
            private:

		stream_t * p_stream;
		virtual void initSchedule();
        };
    }
}

#endif /* MPDMANAGER_H_ */
