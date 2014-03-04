/* * MPD.h
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

#ifndef MPD_H_
#define MPD_H_

#include <vector>
#include <string>
#include <map>

#include "Period.h"


namespace dash
{
    namespace mpd
    {
        class MPD
        {
            public:
                MPD();
                virtual ~MPD();


		
                virtual bool                            isLive() const;
                virtual void                            setLive( bool live );
                virtual time_t                          getAvailabilityStartTime() const;
                virtual void                            setAvailabilityStartTime( time_t time );
                virtual time_t                          getAvailabilityEndTime() const;
                virtual void                            setAvailabilityEndTime( time_t time );
                virtual time_t                          getDuration() const;
                virtual void                            setDuration( time_t duration );
                virtual time_t                          getMinUpdatePeriod() const;
                virtual void                            setMinUpdatePeriod( time_t period );
                virtual time_t                          getMinBufferTime() const;
                virtual void                            setMinBufferTime( time_t time );
                virtual time_t                          getTimeShiftBufferDepth() const;
                virtual void                            setTimeShiftBufferDepth( time_t depth );
                virtual const std::vector<std::string *>&   getBaseUrls() const;
                virtual const std::vector<Period *>&    getPeriods() const;
   
		virtual void addPeriod(Period * p);

                virtual void    addBaseUrl              (std::string *url);
   

            private:

                bool                                live;
                time_t                              availabilityStartTime;
                time_t                              availabilityEndTime;
                time_t                              duration;
                time_t                              minUpdatePeriod;
                time_t                              minBufferTime;
                time_t                              timeShiftBufferDepth;
                std::vector<Period *>               periods;
                std::vector<std::string *>          baseUrls;
        };
    }
}
#endif /* MPD_H_ */
