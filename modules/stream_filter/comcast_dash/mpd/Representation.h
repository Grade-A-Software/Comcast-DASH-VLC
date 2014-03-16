/*
 * Representation.h
 */

#ifndef REPRESENTATION_H_
#define REPRESENTATION_H_

#include <string>
#include <cstdlib>
#include <vector>
#include "Segment.h"

namespace   comcast_dash
{
    namespace mpd
    {
        
        class Representation
        {
        public:
            Representation();
            virtual ~Representation ();
            
            const std::string&  getId() const;
            void setId( const std::string &id );
            /*
             *  @return The bitrate required for this representation
             *          in bits per seconds.
             *          Will be a valid value, as the parser refuses Representation
             *          without bandwidth.
             */
            int getBandwidth() const;
            void setBandwidth(int bandwidth);
            
            int getSampleRate() const;
            void setSampleRate(int sampleRate);
            
            void setWidth(int width);
            int getWidth() const;
            
            void setHeight(int height);
            int getHeight() const;
            
        private:
            std::string id;
            int bandwidth;
            int sampleRate;
            int width;
            int height;
            
        };
    }
}

#endif /* REPRESENTATION_H_ */
