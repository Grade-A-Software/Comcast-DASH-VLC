/*
 * MPD.cpp
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

#include <limits>
#include "MPD.h"

using namespace comcast_dash::mpd;
using namespace comcast_dash::http;

MPD::MPD () : count(0)
{
}

MPD::~MPD   ()
{
    vlc_delete_all( this->periods );
}

const std::vector<Period*>& MPD::getPeriods() const
{
    return this->periods;
}

void MPD::addPeriod(Period *period)
{
    this->periods.push_back(period);
}



Chunk* MPD::getNextChunk(){
    Chunk *chunk = new Chunk();
    if (count++ < this->getTimeLineURLs().size()){
        chunk->setUrl(this->getTimeLineURLs().at(count-1));
        chunk->setBitrate(this->getWorstRepresentation()->getBandwidth());
        return chunk;
    }
    return NULL;
}

Representation* MPD::getWorstRepresentation() {
    Representation *toReturn = NULL;
    for (size_t p = 0; p < periods.size(); p++) {
        std::vector<AdaptationSet *>  adaptationSets = periods.at(p)->getAdaptationSets();
        for (size_t a = 0; a < adaptationSets.size(); a++) {
            std::string contentType = adaptationSets.at(a)->getContentType();
            if (contentType.compare("muxed")==0) {
                
                
                std::vector<Representation *>  representations = adaptationSets.at(a)->getRepresentations();
                std::vector<Segment *>  segments = adaptationSets.at(a)->getSegments();
                int minBandwidth = std::numeric_limits<int>::max();;
                int minRepIndex = std::numeric_limits<int>::max();;
                for (size_t r = 0; r < representations.size(); r++) {
                    int tempBandwidth = representations.at(r)->getBandwidth();
                    if(tempBandwidth<minBandwidth){
                        minRepIndex = r;
                        minBandwidth=tempBandwidth;
                    }
                }
                toReturn = representations.at(minRepIndex);
            }
        }
    }
    return toReturn;
}

std::vector<std::string> MPD::getURLs()
{
    std::vector<std::string> urls;
    for (size_t p = 0; p < periods.size(); p++) {
        std::vector<AdaptationSet *>  adaptationSets = periods.at(p)->getAdaptationSets();
        for (size_t a = 0; a < adaptationSets.size(); a++) {
            urls.push_back("");
            urls.push_back("AdaptionSet: " + adaptationSets.at(a)->getId());
            urls.push_back("Content Type: " + adaptationSets.at(a)->getContentType());
            std::vector<Representation *>  representations = adaptationSets.at(a)->getRepresentations();
            std::vector<Segment *>  segments = adaptationSets.at(a)->getSegments();
            for (size_t r = 0; r < representations.size(); r++) {
                for (size_t s = 0; s < segments.size(); s++) {
                    std::stringstream ss;
                    int time = segments.at(s)->getTime();
                    std::stringstream ssTime;
                    ssTime << time;
                    std::string timestr = ssTime.str();
                    
                    std::string rep_id = representations.at(r)->getId();
                    
                    
                    std::string segmentTemplate = adaptationSets.at(a)->getSegmentTemplate();
                    size_t index = 0;
                    while (true) {
                        std::string toFindString = "$RepresentationID$";
                        /* Locate the substring to replace. */
                        index = segmentTemplate.find(toFindString, index);
                        if (index == std::string::npos) break;
                        
                        /* Make the replacement. */
                        segmentTemplate.replace(index, toFindString.length(), rep_id);
                        
                        /* Advance index forward so the next iteration doesn't pick it up as well. */
                        index += toFindString.length();
                    }
                    
                    index = 0;
                    while (true) {
                        std::string toFindString = "$Time$";
                        /* Locate the substring to replace. */
                        index = segmentTemplate.find(toFindString, index);
                        if (index == std::string::npos) break;
                        
                        /* Make the replacement. */
                        segmentTemplate.replace(index, toFindString.length(), timestr);
                        
                        /* Advance index forward so the next iteration doesn't pick it up as well. */
                        index += toFindString.length();
                    }
                    
                    
                    ss << adaptationSets.at(a)->getBaseURL() << segmentTemplate;
                    urls.push_back(ss.str());
                    
                }
            }
        }
    }
    return urls;
    
}

std::vector<std::string> MPD::getTimeLineURLs()
{
    std::vector<std::string> urls;
    for (size_t p = 0; p < periods.size(); p++) {
        std::vector<AdaptationSet *>  adaptationSets = periods.at(p)->getAdaptationSets();
        for (size_t a = 0; a < adaptationSets.size(); a++) {
            std::string contentType = adaptationSets.at(a)->getContentType();
            if (contentType.compare("muxed")==0) {
                
                
                std::vector<Representation *>  representations = adaptationSets.at(a)->getRepresentations();
                std::vector<Segment *>  segments = adaptationSets.at(a)->getSegments();
                int minBandwidth = std::numeric_limits<int>::max();;
                int minRepIndex = std::numeric_limits<int>::max();;
                for (size_t r = 0; r < representations.size(); r++) {
                    int tempBandwidth = representations.at(r)->getBandwidth();
                    if(tempBandwidth<minBandwidth){
                        minRepIndex = r;
                        minBandwidth=tempBandwidth;
                    }
                }
                
                for (size_t s = 0; s < segments.size(); s++) {
                    
                    int repeat = segments.at(s)->getRepeat();
                    int time = segments.at(s)->getTime();
                    for (int l = 0; l<repeat; l++) {
                        
                        std::stringstream ss;
                        std::stringstream ssTime;
                        ssTime << time;
                        std::string timestr = ssTime.str();
                        
                        std::string rep_id = representations.at(minRepIndex)->getId();
                        
                        std::string segmentTemplate = adaptationSets.at(a)->getSegmentTemplate();
                        size_t index = 0;
                        while (true) {
                            std::string toFindString = "$RepresentationID$";
                            /* Locate the substring to replace. */
                            index = segmentTemplate.find(toFindString, index);
                            if (index == std::string::npos) break;
                            
                            /* Make the replacement. */
                            segmentTemplate.replace(index, toFindString.length(), rep_id);
                            
                            /* Advance index forward so the next iteration doesn't pick it up as well. */
                            index += toFindString.length();
                        }
                        
                        index = 0;
                        while (true) {
                            std::string toFindString = "$Time$";
                            /* Locate the substring to replace. */
                            index = segmentTemplate.find(toFindString, index);
                            if (index == std::string::npos) break;
                            
                            /* Make the replacement. */
                            segmentTemplate.replace(index, toFindString.length(), timestr);
                            
                            /* Advance index forward so the next iteration doesn't pick it up as well. */
                            index += toFindString.length();
                        }
                        
                        time = time + segments.at(s)->getDuration();
                        ss << adaptationSets.at(a)->getBaseURL() << segmentTemplate;
                        urls.push_back(ss.str());
                        
                    }

            }
        }
    }
}
return urls;

}
