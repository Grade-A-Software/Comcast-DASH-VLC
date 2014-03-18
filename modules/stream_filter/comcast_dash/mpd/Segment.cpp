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

using namespace comcast_dash::mpd;

Segment::Segment() :
duration(0),
repeat(0),
time(0)
{
    
}

Segment::~Segment()
{
    
}


int Segment::getDuration()
{
    return this->duration;
}
void Segment::setDuration(int d)
{
    this->duration = d;
}

int Segment::getRepeat()
{
    return this->repeat;
}
void Segment::setRepeat(int r)
{
    this->repeat = r;
}

int Segment::getTime()
{
    return this->time;
}
void Segment::setTime(int t)
{
    this->time = t;
}



