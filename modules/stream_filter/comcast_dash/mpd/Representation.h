/*
 * Representation.h
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

#ifndef REPRESENTATION_H_
#define REPRESENTATION_H_

#include <string>
<<<<<<< HEAD

#include "Segment.h"

namespace dash
{
    namespace mpd
    {
        class AdaptationSet;

        class Representation
        {
            public:
                Representation();
                virtual ~Representation ();

                virtual const std::string&  getId                   () const;
                virtual void                setId                   ( const std::string &id );
                /*
                 *  @return The bitrate required for this representation
                 *          in bits per seconds.
                 *          Will be a valid value, as the parser refuses Representation
                 *          without bandwidth.
                 */
                virtual uint64_t            getBandwidth            () const;
                virtual void                setBandwidth            ( uint64_t bandwidth );
		virtual const AdaptationSet*        getParentGroup() const;
                virtual void                setParentGroup( const AdaptationSet *group );

                
                virtual void                setWidth                (int width);
                virtual int                 getWidth                () const;
                virtual void                setHeight               (int height);
                virtual int                 getHeight               () const;

            private:
                uint64_t                            bandwidth;
                std::string                         id;
                
                
		const AdaptationSet                         *parentGroup;
                

		
                int                                 width;
                int                                 height;
=======
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
            
>>>>>>> 69d723081c8842f51f638be671f61258df24ec2b
        };
    }
}

#endif /* REPRESENTATION_H_ */
