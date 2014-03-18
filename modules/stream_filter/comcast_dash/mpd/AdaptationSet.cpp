/*
 * AdaptationSet.cpp
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

#include "AdaptationSet.h"

#include <vlc_common.h>
#include <vlc_arrays.h>

using namespace comcast_dash::mpd;

AdaptationSet::AdaptationSet()
{
}

AdaptationSet::~AdaptationSet()
{
    vlc_delete_all( this->representations );
    vlc_delete_all( this->segments );
}

const std::string& AdaptationSet::getId() const
{
    return this->id;
}

void AdaptationSet::setId(const std::string &id)
{
    if ( id.empty() == false )
        this->id = id;
}

std::vector<Representation*> AdaptationSet::getRepresentations()
{
    return this->representations;
}

void AdaptationSet::addRepresentation(Representation *rep)
{
    this->representations.push_back(rep);
}

std::vector<Segment *> AdaptationSet::getSegments()
{
    return this->segments;
}

void AdaptationSet::addSegment( Segment *seg )
{
    this->segments.push_back(seg);
}

std::string AdaptationSet::getContentType()
{
    return this->contentType;
}

void AdaptationSet::setContentType(std::string contentType)
{
    this->contentType = contentType;
}

std::string AdaptationSet::getBaseURL()
{
    return this->baseURL;
}

void AdaptationSet::setBaseURL(std::string baseURL)
{
    this->baseURL = baseURL;
}

std::string AdaptationSet::getSegmentTemplate()
{
    return this->segmentTemplate;
}
void AdaptationSet::setSegmentTemplate(std::string st)
{
    this->segmentTemplate = st;
}
