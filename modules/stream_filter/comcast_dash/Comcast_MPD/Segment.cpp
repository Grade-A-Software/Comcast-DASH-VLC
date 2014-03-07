/*
 * Segment.cpp
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
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cstdlib>

#include "Segment.h"

 using namespace comcast_dash::Comcast_MPD;

 Segment::Segment(Node * n, Representation * r) :
	 length(0),
	 repeat(0),
	 time(NULL),
	 node(n),
	 rep(r)
 {

 }

 Segment::~Segment()
 {

 }

 std::string getFileName()
 {

 }

 void parseAttributes(Node * n)
 {

 }

 int getLength()
 {
	 return this->length;
 }
 int getRepeat()
 {
	 return this->repeat;
 }
 std::string getTime()
 {
	 return this->time;
 }
 void setLength(int l)
 {
	 this->length = l;
 }
 void setRepeat(int r)
 {
	 this->repeat = r;
 }
 void setTime(std::string st)
 {
	 this->time = st;
 }
	