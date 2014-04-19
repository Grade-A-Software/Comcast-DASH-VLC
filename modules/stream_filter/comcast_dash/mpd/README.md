####MPD

#####Overview:
An MPD object holds the data that is represented in the different nodes of an XML document tree.
The format of the XML that is parsed (by different classes) into Nodes and eventually into an MPD object is   
&nbsp;&nbsp;&nbsp; Period  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;AdaptationSet  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Representation  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Segment  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;More AdaptationSets  


An MPD object has Periods.  
&nbsp;&nbsp;&nbsp;&nbsp;A Period has AdaptationSets.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;AdaptationSets have Representations and a Segment.  


An MPD object is instantiated in Comcast_dash\parser.cpp

#####MPD.cpp
	An MPD object has a vector<Period *> .
	getPeriods() returns the vector<Period *>.
	addPeriod(Period*) adds a pointer to a period to the end of the vector. 
	getWorstRepresentation()
		Loops through the vector<Period*> and through the adaptationSets for each Period.
		Returns the Representation that has the smallest (minimum) bandwidth. 
	getURLs()
		Creates a vector<string> of Urls of where to find the media.
		For each adaptationSet, get representations and segments. Get segment Time and RepresentationId.
		Get the segmentTemplate. Replace "$RepresentationID$" with the RepresentationID, and replace "$Time$" with Time. 
		After these values have been replaced, concatenate the baseUrl of the adaptationSet and this segmentTemplate and 
		append this string to the end of the urls vector. 
	getTimeLineURLs()
		Creates a vector<string> of Urls with the lowest bitrate. 

#####Period.cpp
	A Period has a collection of pointers to AdaptationSets stored in a vector<AdaptationSet *>
	getAdaptationSets() 
		returns the address of the vector<AdaptationSet *>
	addAdaptationSet(AdaptationSet *AdapationSet)
		adds a pointer to the end of the vector<AdaptationSet *>

#####AdaptationSet.cpp
	An AdaptationSet a vector<Representation *> and a vector<Segment *> as well as strings representing the 
	attributes found in the xml:
		id
		contentType
		baseURL
		segmentTemplate
	The class also has accessor/mutator functions for each of the data members. 

#####Representation.cpp
	A Representation has data members representing the attributues found in the xml:
		string id
		int bandwidth
		    sampleRate
		    width
		    height
	Each of the data members has getter/setter functions that only get and set the values.
	getBandwidth() 
		Returns the bitrate required for this representation in bits per second. 
		The validity of this value is checked in the parser. 

#####Segment.cpp
	A Segment has three data members along with functions for setting/getting their values:
		int duration
		    repeat
		    time
	The members correspond to the attributes in the xml.
	
	
		
		
	
		
