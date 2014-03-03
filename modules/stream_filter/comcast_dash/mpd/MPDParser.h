/*
 * IsoffMainParser.h
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

#ifndef ISOFFMAINPARSER_H_
#define ISOFFMAINPARSER_H_

#include "xml/Node.h"
#include "xml/DOMHelper.h"
#include "mpd/MPD.h"
#include "mpd/Period.h"
#include "mpd/AdaptationSet.h"
#include "mpd/Representation.h"
#include "mpd/Segment.h"

#include <cstdlib>
#include <sstream>

#include <vlc_common.h>
#include <vlc_stream.h>
#include <vlc_strings.h>

namespace dash
{
    namespace mpd
    {
        class MPDParser
        {
            public:
                MPDParser             (dash::xml::Node *root, stream_t *p_stream);
                virtual ~MPDParser    ();

                bool    parse  ();
                MPD*    getMPD ();

            private:
                dash::xml::Node *root;
                stream_t        *p_stream;
                MPD             *mpd;
                Representation  *currentRepresentation;

                void    setPeriods          ();
                void    setAdaptationSets   (dash::xml::Node *periodNode, Period *period);
                void    setRepresentations  (dash::xml::Node *adaptationSetNode, AdaptationSet *adaptationSet);

                void    setSegments         (dash::xml::Node *adaptatinoSetNode, AdaptationSet *adaptationSet);
		void    setBaseURL          (dash::xml::Node *adaptationSetNode, AdaptationSet *adaptationSet)
        };
    }
}

#endif /* ISOFFMAINPARSER_H_ */
