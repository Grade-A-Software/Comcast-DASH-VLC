/*
 * Representation.h
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

#ifndef REPRESENTATION_H_
#define REPRESENTATION_H_

#include <string>
#include <cstdlib>
#include "Segment.h"
#include "AdaptationSet.h"
#include "xml/Node.h"
#include "xml/DOMHelper.h"

namespace   comcast_dash
{
    namespace Comcast_MPD
    {

        class Representation : AdaptationSet
        {
            public:
                Representation(Node *);
                virtual ~Representation ();
                
                int getBandwidth();
                void setBandwidth();
                string getId();
                void setId();
                std:vector<Segment *> getSegments();
                void setSegments(vector<Segment *>);
                parseAttributes(Node*);
                
               
            private:
                int bandwidth;
                std::string id;
                std:vector<Segment> segments;

        };
    }
}

#endif /* REPRESENTATION_H_ */
