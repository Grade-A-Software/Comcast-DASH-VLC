/*
 * Representation.cpp
 *****************************************************************************
 * Copyright (C) 2014 Grade-A-Software
 *
 * Created on: March 5, 2014
 * Author:  Scott Allen
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

 using namespace comcast_dash::Comcast_MPD;

 Representation::Representation  (Node * n) :
	bandwidth (0),
	id (0)
 {
 }

 Representation::~Representation ()
 {
 }

 const std::string&  Representation::getId  () const
 {
    return this->id;
}

void    Representation::setId(const std::string &id)
{
    if ( id.empty() == false )
        this->id = id;
}

int     Representation::getBandwidth  () const
{
    return this->bandwidth;
}

void    Representation::setBandwidth( int bandwidth )
{
    this->bandwidth = bandwidth;
}

std::list<const Segment*>    Representation::getSegments  () const
{
    return this->segments;
}
void     Representation::setSegments (std::vector<const Segment*> list)
{
    this->segments = list;
}
void	Representation::parseAttributes(Node * node)
{
	Representation::setSegments(DOMHelper::getElementByTagName(node, "S", false);
	std::string st_id = (node->getAttributeValue("id"));
	this->id = atoi(st_id);
	std::string st_bw = (node->getAttributeValue("bandwidth"));
	this->setBandwidth = atoi(st_bw);

}

