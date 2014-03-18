/*
 * Segment.h
 *****************************************************************************
<<<<<<< HEAD
 * Copyright (C) 2010 - 2011 Klagenfurt University
 *
 * Created on: Aug 10, 2010
 * Authors: Christopher Mueller <christopher.mueller@itec.uni-klu.ac.at>
 *          Christian Timmerer  <christian.timmerer@itec.uni-klu.ac.at>
=======
 * Copyright (C) 2014 Grade-A-Software
 *
 * Created on: March 5, 2014
 * Author: Scott Allen
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
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
<<<<<<< HEAD
#include <sstream>
#include <vector>
#include "../http/Chunk.h"
#include "../xml/Node.h"
#include "../xml/DOMParser.h"
using namespace dash;
using namespace dash::http;
using namespace dash::xml;
namespace dash
{
    namespace mpd
    {
        class Representation;
        class Segment
        {
            public:
	  Segment( Node * root, const Representation *parent );
                virtual ~Segment(){}
                std::string getSourceUrl() const;
                void        setSourceUrl( const std::string &url );
                /**
                 *  @return true if the segment should be dropped after being read.
                 *          That is basically true when using an Url, and false
                 *          when using an UrlTemplate
                 */
                bool                            isSingleShot    () const;
                void                            done            ();
                void                            addBaseUrl      (std::string *url);
                void setTime(std::string *time);
	        std::string* getTime();
                void setRepeat(std::string *repeat);
	        std::string* getRepeat();
		void setDuration(std::string *duration);
	        std::string* getDuration();

                void                            setByteRange    (int start, int end);
                int                             getStartByte    () const;
                int                             getEndByte      () const;
                dash::http::Chunk*              toChunk         ();
                const Representation*                   getParentRepresentation() const;
                int                             getSize() const;

            protected:
                std::string             sourceUrl;
                std::vector<std::string *>  baseUrls;
                int                     startByte;
                int                     endByte;
                const Representation*   parentRepresentation;
                int                     size;
=======
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
            
        private:
            int duration;
            int repeat;
            int time;
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
        };
    }
}

#endif /* SEGMENT_H_ */
