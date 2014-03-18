/*
 * Representation.cpp
<<<<<<< HEAD
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
=======
 */
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cstdlib>

#include "Representation.h"

<<<<<<< HEAD
using namespace dash::mpd;

Representation::Representation  () :
                bandwidth       (0),
                qualityRanking  ( -1 ),
                parentGroup     ( NULL ),
                width           (0),
                height          (0)

{
=======
using namespace comcast_dash::mpd;

Representation::Representation  () :
bandwidth       (0),
sampleRate      ( 0 ),
width           (0),
height          (0)

{
    
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
}

Representation::~Representation ()
{
}

<<<<<<< HEAD
const std::string&  Representation::getId                   () const
=======
const std::string& Representation::getId() const
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
{
    return this->id;
}

<<<<<<< HEAD
void    Representation::setId(const std::string &id)
=======
void Representation::setId(const std::string &id)
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
{
    if ( id.empty() == false )
        this->id = id;
}

<<<<<<< HEAD
uint64_t     Representation::getBandwidth            () const
=======
int Representation::getBandwidth() const
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
{
    return this->bandwidth;
}

<<<<<<< HEAD
void    Representation::setBandwidth( uint64_t bandwidth )
=======
void Representation::setBandwidth( int bandwidth )
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
{
    this->bandwidth = bandwidth;
}


<<<<<<< HEAD


const AdaptationSet *Representation::getParentGroup() const
{
    return this->parentGroup;
}

void Representation::setParentGroup(const AdaptationSet *group)
{
    if ( group != NULL )
        this->parentGroup = group;
}

int Representation::getQualityRanking() const
{
    return this->qualityRanking;
}

void Representation::setQualityRanking( int qualityRanking )
{
    if ( qualityRanking > 0 )
        this->qualityRanking = qualityRanking;
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
=======
int Representation::getSampleRate() const
{
    return this->sampleRate;
}

void Representation::setSampleRate( int sampleRate )
{
    this->sampleRate = sampleRate;
}

void Representation::setWidth(int width)
{
    this->width = width;
}
int Representation::getWidth() const
{
    return this->width;
}
void Representation::setHeight(int height)
{
    this->height = height;
}
int Representation::getHeight() const
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
{
    return this->height;
}
