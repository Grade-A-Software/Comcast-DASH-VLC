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

using namespace dash::mpd;
using namespace dash::http;

Segment::Segment(Node * segmentNode, Representation * rep) :
        startByte  (-1),
        endByte    (-1),
	representation (rep)
{
  this->setTime(segmentNode->getAttributeText("t"));
  this->setRepeat(segmentNode->getAttributeText("r"));
  this->setDuration(segmentNode->getAttributeText("d"));
  this->setSourceUrl();
}

bool                    Segment::isSingleShot   () const
{
    return true;
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
dash::http::Chunk*      Segment::toChunk        ()
{
    Chunk *chunk = new Chunk();

    if(this->startByte != -1 && this->endByte != -1)
    {
        chunk->setUseByteRange(true);
        chunk->setStartByte(this->startByte);
        chunk->setEndByte(this->endByte);
    }

    if(this->baseUrls.size() > 0)
    {
        std::stringstream ss;
        ss << this->representation->getParentGroup()->getBaseURL() << this->representation->getId() << "-" << this->time << ".ts";
        chunk->setUrl(ss.str());
        ss.clear();
    }

    chunk->setBitrate(this->representation->getBandwidth());

    return chunk;
}

const Representation *Segment::getRepresentation() const
{
    return this->representation;
}

int Segment::getSize() const
{
  return this->representation->getBandwidth() * std::stoi(this->duration);
}
