/*
 * Representation.cpp
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

#include <cstdlib>

#include "Representation.h"

 using namespace comcast_dash::mpd;

 Representation::Representation  () :
 bandwidth       (0),
 codecs          ( NULL ),
 sampleRate      ( 0 ),
 frameRate       ( NULL ),
 segmentList     ( NULL ),
 width           (0),
 height          (0)

 {
 }

 Representation::~Representation ()
 {
 }

 const std::string&  Representation::getId                   () const
 {
    return this->id;
}

void    Representation::setId(const std::string &id)
{
    if ( id.empty() == false )
        this->id = id;
}

uint64_t     Representation::getBandwidth            () const
{
    return this->bandwidth;
}

void    Representation::setBandwidth( uint64_t bandwidth )
{
    this->bandwidth = bandwidth;
}

std::string&  Representation::getCodecs                   () const
{
    return this->codecs;
}

void    Representation::setCodecs(std::string &codecs)
{
    if ( codecs.empty() == false )
        this->codecs = codecs;
}

uint64_t     Representation::getSampleRate           () const
{
    return this->sampleRate;
}

void    Representation::setSampleRate ( uint64_t sampleRate )
{
    this->sampleRate = sampleRate;
}

std::string&  Representation::getFrameRate                   () const
{
    return this->frameRate;
}

void    Representation::setFrameRate( std::string &frameRate)
{
    if ( frameRate.empty() == false )
        this->frameRate = frameRate;
}

std::list<const Segment*>        Representation::getSegmentList          () const
{
    return this->segmentList;
}
void                Representation::setSegmentList          (std::list<const Segment*> list)
{
    this->segmentList = list;
}

void                Representation::setWidth                (int width)
{
    this->width = width;
}
int                 Representation::getWidth                () const
{
    return this->width;
}
void                Representation::setHeight               (int height)
{
    this->height = height;
}
int                 Representation::getHeight               () const
{
    return this->height;
}
