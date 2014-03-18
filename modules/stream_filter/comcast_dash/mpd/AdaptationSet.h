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
#include "mpd/Segment.h"

namespace comcast_dash
{
    namespace mpd
    {
        class Representation;
        
        class Segment;
        
        class AdaptationSet 
        {
        public:
            AdaptationSet();
            virtual ~AdaptationSet();
            
            const std::string&  getId() const;
            void setId( const std::string &id );
            
            std::vector<Representation *> getRepresentations();
            void addRepresentation( Representation *rep );
            
            std::vector<Segment *> getSegments();
            void addSegment( Segment *seg );
            
            std::string getContentType();
            void setContentType(std::string contentType);
            
            std::string getBaseURL();
            void setBaseURL(std::string baseURL);
            
            std::string getSegmentTemplate();
            void setSegmentTemplate(std::string st);
            
        private:
            std::string id;
            std::vector<Representation *> representations;
            std::vector<Segment *> segments;
            std::string contentType;
            std::string baseURL;
            std::string segmentTemplate;

        };
    }
}

#endif /* ADAPTATIONSET_H_ */
