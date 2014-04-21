####AdaptationLogic

AdaptationLogic allows for switching to different bitrates depending on a varying bandwidth. 

######There are two types of AdaptationLogic:
	1. RateBasedAdaptationLogic	
	2. AlwaysBestAdaptationLogic

	They each have a method to get the current representation:
		getCurentRepresentation()

######	RateBasedAdaptationLogic
		getNextChunk()
		uses the mpdManager to get the Representation from the currentPeriod at the 
		specified bitrate. The segments of that Representation are then assigned to 
		a vector<Segment*>. The Url is then obtained from those Segments. 

######	AlwaysBestAdaptationLogic
		initSchedule() 
		uses the mpdManager to get the best Representation and assigns the Segments from that
		Representation to a vector<Segment *>

		GetNextChunk() 
		Gets the Url from the segments in the vector<Segment*>

######	Both RateBased and AlwaysBest extend AbstractAdaptationLogic
	
######	AbstractAdaptationLogic
		bufferLevelChanged(mtime_t,int)
		bufferedMicroSec and bufferedPercent are both set with the parameters passed to the method.

		downloadRateChanged(uint64_t, uint64_t)
		bpsAvg and bpsLastChunk are both set with the parameters passed to the method.

		getBpsAvg()
		returns bpsAvg
	
		getBpsLastChunk()
		returns bpsLastChunk

		getBufferedPercent()
		returns bufferedPercent



######	AbstractAdaptationLogic extends IAdaptationLogic
	
######	IadaptationLogic extends AdaptationLogic::IDownloadRateObserver and dash::buffer::IBufferObserver

	
