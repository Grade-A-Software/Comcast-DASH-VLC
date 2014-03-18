/*
 * AlwaysBestAdaptationLogic.h
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

#ifndef ALWAYSBESTADAPTATIONLOGIC_H_
#define ALWAYSBESTADAPTATIONLOGIC_H_

#include "adaptationlogic/AbstractAdaptationLogic.h"
#include "http/Chunk.h"
#include "xml/Node.h"
#include "mpd/IMPDManager.h"
#include "mpd/Period.h"
#include "mpd/Segment.h"
#include "mpd/BasicCMManager.h"
#include <vector>

namespace comcast_dash
{
    namespace logic
    {
        class AlwaysBestAdaptationLogic : public AbstractAdaptationLogic
        {
            public:
                AlwaysBestAdaptationLogic           (comcast_dash::mpd::IMPDManager *mpdManager, stream_t *stream);
                virtual ~AlwaysBestAdaptationLogic  ();

                comcast_dash::http::Chunk* getNextChunk();
                const mpd::Representation *getCurrentRepresentation() const;

            private:
                std::vector<mpd::Segment *>         schedule;
                comcast_dash::mpd::IMPDManager              *mpdManager;
                size_t                              count;
                comcast_dash::mpd::Representation           *bestRepresentation;

                void initSchedule();
        };
    }
}

#endif /* ALWAYSBESTADAPTATIONLOGIC_H_ */
