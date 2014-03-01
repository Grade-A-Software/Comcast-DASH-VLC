/*
 * Representation.h
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

#ifndef REPRESENTATION_H_
#define REPRESENTATION_H_

#include <string>

namespace   comcast_dash
{
    namespace mpd
    {

        class Representation 
        {
            public:
                Representation();
                virtual ~Representation ();

                const std::string&  getId                   () const;
                void                setId                   ( const std::string &id );
                /*
                 *  @return The bitrate required for this representation
                 *          in bits per seconds.
                 *          Will be a valid value, as the parser refuses Representation
                 *          without bandwidth.
                 */
                uint64_t            getBandwidth            () const;
                void                setBandwidth            ( uint64_t bandwidth );

                std::string&        getCodecs               () const;
                void                setCodecs               (std::string& codecs );

                uint64_t            getSampleRate               () const;
                void                setSampleRate               (uint64_t sampleRate );
                
                std::string&        getFrameRate               () const;
                void                setFrameRate               (std::string& frameRate );

                const std::list<const Segment*>&     getSegmentList() const;
                void                setSegmentList          ( const Segment* dep );

                void                setWidth                (int width);
                int                 getWidth                () const;

                void                setHeight               (int height);
                int                 getHeight               () const;

            private:
                uint64_t                            bandwidth;
                std::string                         id;
                std::string                         codecs;
                std::list<const Segment*>           segmentList;
                std::string                         frameRate
                uint64_t                            sampleRate;
                int                                 width;
                int                                 height;

        };
    }
}

#endif /* REPRESENTATION_H_ */
