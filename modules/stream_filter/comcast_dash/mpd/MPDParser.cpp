/*
 * IsoffMainParser.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2012 Klagenfurt University
 *
 * Created on: Jan 27, 2012
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

#include "MPDParser.h"

using namespace dash::mpd;
using namespace dash::xml;

MPDParser::MPDParser    (Node *root, stream_t *p_stream) :
                 root               (root),
                 p_stream           (p_stream),
                 mpd                (NULL),
                 currentRepresentation( NULL )
{
  this->mpd = new MPD();
  this->setPeriods();
}
MPDParser::~MPDParser   ()
{
}

MPD* MPDParser::getMPD             ()
{
    return this->mpd;
}

void MPDParser::setPeriods()
{
    std::vector<Node *> periods = DOMHelper::getElementByTagName(this->root, "Period", false);

    for(size_t i = 0; i < periods.size(); i++)
    {
        Period *period = new Period();
        this->setAdaptationSets(periods.at(i), period);
        this->mpd->addPeriod(period);
    }
}
void MPDParser::setAdaptationSets(Node *periodNode, Period *period)
{
    std::vector<Node *> adaptationSets = DOMHelper::getElementByTagName(periodNode, "AdaptationSet", false);

    for(size_t i = 0; i < adaptationSets.size(); i++)
    {
        AdaptationSet *adaptationSet = new AdaptationSet();
        this->setRepresentations(adaptationSets.at(i), adaptationSet);
	this->setSegments(adaptationSets.at(i), adaptationSet);
	this->setBaseURL(adaptationSets.at(i), adaptationSet);
        period->addAdaptationSet(adaptationSet);
    }
}
void MPDParser::setBaseURL(Node *adaptationSetNode, AdaptationSet *adaptationSet)
{
  std::vector<Node *> urls = DOMHelper::getElementByTagName(adaptationSetNode, "BaseURL", false);
  Node * url = urls.at(0);
  adaptationSet->setBaseURL(url->getText());
}

void MPDParser::setRepresentations(Node *adaptationSetNode, AdaptationSet *adaptationSet)
{
    std::vector<Node *> representations = DOMHelper::getElementByTagName(adaptationSetNode, "Representation", false);

    for(size_t i = 0; i < representations.size(); i++)
    {
        this->currentRepresentation = new Representation;
        Node *repNode = representations.at(i);

        if(repNode->hasAttribute("width"))
            this->currentRepresentation->setWidth(atoi(repNode->getAttributeValue("width").c_str()));

        if(repNode->hasAttribute("height"))
            this->currentRepresentation->setHeight(atoi(repNode->getAttributeValue("height").c_str()));

        if(repNode->hasAttribute("bandwidth"))
            this->currentRepresentation->setBandwidth(atoi(repNode->getAttributeValue("bandwidth").c_str()));

	adaptationSet->addRepresentation(this->currentRepresentation);
	this->currentRepresentation->setParentGroup(adaptationSet);
    }
}

void MPDParser::setSegments(Node * adaptationSetNode, AdaptationSet *adaptationSet, Representation *rep)
{
    std::vector<Node *> segments = DOMHelper::getElementByTagName(adaptationSetNode, "S", false);

    for(size_t i = 0; i < segments.size(); i++)
    {
      Segment * seg = new Segment(segments.at(i),rep);
      adaptationSet->addSegment(seg);
    }
}
