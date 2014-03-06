 /*
 *AdapationSet.h
 *****************************************************************************
 * Copyright (C) 2014 Grade A Software
 *
 * Created on: March 5, 2014
 * Authors: Scott Dykstra <sdykstr44@gmail.com>
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
#include <cstdlib>
#include "xml/Node.h"
#include <vector>
#include <Segments.h>
#include <Representations.h>

namespace dash;
namespace xml;
     class AdapationSet ::Period
     {
	public:
		                
	    		        	AdaptionSet  (Node *root);
	    void			parseAttributes(Node *root);
	    string			getBaseURL();
	    void			setBaseURL(Node*);
	    void 			setSegments(Node*);
	    vector<Segment*>		getSegments();
	    void			setRepresentations(Node*);
	    vector<Representation*>	getRepresentations();


 	    std::vector<Segments> segments;
	    vector<Representation*> representations;
    	    string baseURL;



}
