/*
 * MPDManager
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Jan 27, 2010
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

#include "MPDManager.h"


using namespace dash;
using namespace dash::mpd;
using namespace dash::xml;
MPDManager::MPDManager(Node * root, stream_t *stream) : p_stream(stream), count(0)
{
  MPDParser *parser = new MPDParser(root,stream->p_source);
  this->mpd = parser->getMPD();
  delete [] parser;
}
MPDManager::~MPDManager()
{
    delete this->mpd;
}

const std::vector<Segment*> MPDManager::getSegments(const Representation *rep)
{
  return rep->getParentGroup()->getSegments();
}
const std::vector<Period*>& MPDManager::getPeriods() const
{
    return this->mpd->getPeriods();
}
Representation* MPDManager::getBestRepresentation (Period *period)
{
    std::vector<AdaptationSet *> adaptationSets = period->getAdaptationSets();

    int             bitrate  = 0;
    Representation  *best    = NULL;

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        std::vector<Representation *> reps = adaptationSets.at(i)->getRepresentations();
        for(size_t j = 0; j < reps.size(); j++)
        {
            int currentBitrate = reps.at(j)->getBandwidth();

            if(currentBitrate > bitrate)
            {
                bitrate = currentBitrate;
                best    = reps.at(j);
            }
        }
    }
    return best;
}
Period* MPDManager::getFirstPeriod()
{
    std::vector<Period *> periods = this->mpd->getPeriods();

    if(periods.size() == 0)
        return NULL;

    return periods.at(0);
}
Representation* MPDManager::getRepresentation     (Period *period, uint64_t bitrate) const
{
    if(period == NULL)
        return NULL;

    std::vector<AdaptationSet *> adaptationSets = period->getAdaptationSets();

    Representation  *best = NULL;

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        std::vector<Representation *> reps = adaptationSets.at(i)->getRepresentations();
        for( size_t j = 0; j < reps.size(); j++ )
        {
            uint64_t currentBitrate = reps.at(j)->getBandwidth();

            if(best == NULL || (currentBitrate > best->getBandwidth() && currentBitrate < bitrate))
            {
                best = reps.at( j );
            }
        }
    }
    return best;
}
Period* MPDManager::getNextPeriod(Period *period)
{
    std::vector<Period *> periods = this->mpd->getPeriods();

    for(size_t i = 0; i < periods.size(); i++)
    {
        if(periods.at(i) == period && (i + 1) < periods.size())
            return periods.at(i + 1);
    }

    return NULL;
}
const MPD* MPDManager::getMPD() const
{
    return this->mpd;
}
Representation* MPDManager::getRepresentation(Period *period, uint64_t bitrate, int width, int height) const
{
    if(period == NULL)
        return NULL;

    std::vector<AdaptationSet *> adaptationSets = period->getAdaptationSets();
    std::vector<Representation *> resMatchReps;

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        std::vector<Representation *> reps = adaptationSets.at(i)->getRepresentations();
        for( size_t j = 0; j < reps.size(); j++ )
        {
            if(reps.at(j)->getWidth() == width && reps.at(j)->getHeight() == height)
                resMatchReps.push_back(reps.at(j));
        }
    }

    if(resMatchReps.size() == 0)
        return this->getRepresentation(period, bitrate);

    Representation  *best = NULL;
    for( size_t j = 0; j < resMatchReps.size(); j++ )
    {
        uint64_t currentBitrate = resMatchReps.at(j)->getBandwidth();

        if(best == NULL || (currentBitrate > best->getBandwidth() && currentBitrate < bitrate))
        {
            best = resMatchReps.at(j);
        }
    }

    return best;
}
Chunk* MPDManager::getNextChunk()
{
  if(this->schedule.size() == 0)
    return NULL;

  if(this->count == this->schedule.size())
    return NULL;

  if ( this->count < this->schedule.size() )
    {
      Chunk *chunk = new Chunk();
      chunk->setUrl(this->schedule.at( this->count )->getSourceUrl());
      this->count++;
      return chunk;
    }
  return NULL;
}
void MPDManager::initSchedule()
{
  std::vector<Period *> periods = this->getPeriods();
  
  for(size_t i = 0; i < periods.size(); i++)
  {
    Representation *best = this->getBestRepresentation(periods.at(i));
    
    if(best != NULL)
    {
      const std::vector<Segment *> segments = best->getParentGroup()->getSegments();
      for(size_t j = 0; j < segments.size(); j++)
      {
	for (int k = 0; k < std::atoi(segments.at(i)->getRepeat()->c_str()); k++)
	this->schedule.push_back(segments.at(j));
      }
    }
  }
}
