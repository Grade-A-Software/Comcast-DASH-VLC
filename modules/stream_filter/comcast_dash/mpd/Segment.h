/*
 * Segment.h
 *****************************************************************************
 * Copyright (C) 2014 Grade-A-Software
 *
 * Created on: March 5, 2014
 * Author: Scott Allen
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

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <string>
#include <cstdlib>

namespace comcast_dash
{
    namespace mpd
    {
        
        class Segment
        {
        public:
            Segment();
            virtual ~Segment ();
            
            int getDuration();
            void setDuration(int d);
            
            int getRepeat();
            void setRepeat(int r);
            
            int getTime();
            void setTime(int t);

            std::string getSegmentTemplate();
            void setSegmentTemplate(std::string st);
            
        private:
            int duration;
            int repeat;
            int time;
            std::string segmentTemplate;
        };
    }
}

#endif /* SEGMENT_H_ */
