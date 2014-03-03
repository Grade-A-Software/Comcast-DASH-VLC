/*
 * Segment.cpp
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
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "Segment.h"
#include "Representation.h"

#include <cassert>

using namespace comcast_dash::mpd;

Segment::Segment(const Representation *parent) :
        startByte  (-1),
        endByte    (-1),
        parentRepresentation( parent )
{
    assert( parent != NULL );
    if ( parent->getSegmentInfo() != NULL && parent->getSegmentInfo()->getDuration() >= 0 )
        this->size = parent->getBandwidth() * parent->getSegmentInfo()->getDuration();
    else
        this->size = -1;
}

std::string             Segment::getSourceUrl   () const
{
    return this->sourceUrl;
}

void                    Segment::setSourceUrl   ( const std::string &url )
{
    if ( url.empty() == false )
        this->sourceUrl = url;
}

void                    Segment::done           ()
{
    //Only used for a SegmentTemplate.
}

void                    Segment::setByteRange   (int start, int end)
{
    this->startByte = start;
    this->endByte   = end;
}
int                     Segment::getStartByte   () const
{
    return this->startByte;
}
int                     Segment::getEndByte     () const
{
    return this->endByte;
}

int						Segment::getTime		() const
{
	return this->time;
}

int						Segment::getId			() const
{
	return this->id;
}

int						Segment::getDuration	() const
{
	return this->duration;
}

int						Segment::getMedia		() const
{
	return this->media;
}
