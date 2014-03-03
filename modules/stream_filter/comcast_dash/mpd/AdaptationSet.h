/*
 * AdaptationSet.h
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

#ifndef ADAPTATIONSET_H_
#define ADAPTATIONSET_H_

#include <vector>
#include <string>
#include <map>

#include "mpd/Representation.h"

namespace dash
{
    namespace mpd
    {
        class SegmentInfoDefault;

        class AdaptationSet 
        {
            public:
                AdaptationSet();
                virtual ~AdaptationSet();

                bool                            getSubsegmentAlignmentFlag() const;
                void                            setSubsegmentAlignmentFlag( bool alignment );
                std::vector<Representation *>   getRepresentations      ();
		std::vector<Segment *>   getSegments      ();
                const Representation*           getRepresentationById   ( const std::string &id ) const;


                void                            setBitstreamSwitching(bool value);
                bool                            getBitstreamSwitching() const;
                void                            addRepresentation( Representation *rep );
		void                            addSegment( Segment *seg );
            private:
                bool                            subsegmentAlignmentFlag;
                std::vector<Representation *>   representations;
		std::vector<Segment *>          segments;
                const SegmentInfoDefault*       segmentInfoDefault;
                bool                            isBitstreamSwitching;
        };
    }
}

#endif /* ADAPTATIONSET_H_ */
