/*
 * Representation.cpp
 */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cstdlib>

#include "Representation.h"

using namespace comcast_dash::mpd;

Representation::Representation  () :
bandwidth       (0),
sampleRate      ( 0 ),
width           (0),
height          (0)

{
    
}

Representation::~Representation ()
{
}

const std::string& Representation::getId() const
{
    return this->id;
}

void Representation::setId(const std::string &id)
{
    if ( id.empty() == false )
        this->id = id;
}

int Representation::getBandwidth() const
{
    return this->bandwidth;
}

void Representation::setBandwidth( int bandwidth )
{
    this->bandwidth = bandwidth;
}


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
{
    return this->height;
}
