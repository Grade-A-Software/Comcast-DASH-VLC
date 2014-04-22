### **Buffering**


Note: This plugin is a work in progress.<br/><br/>
The purpose of this plugin is to play Comcast's version of DASH in VLC.<br />

**Plugin Process**<br />
An overview of the process this plugin will follow can be found [HERE](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Plugin-Process)

#### Files

**[IBufferObserver.h](https://github.com/Grade-A-Software/Comcast-DASH-VLC/blob/master/modules/stream_filter/comcast_dash/buffer/IBufferObserver.h)**<br />
	

**[BlockBuffer.h](https://github.com/Grade-A-Software/Comcast-DASH-VLC/blob/master/modules/stream_filter/comcast_dash/buffer/BlockBuffer.h)**<br />

BlockBuffer.h-

**[BlockBuffer.cpp](https://github.com/Grade-A-Software/Comcast-DASH-VLC/blob/master/modules/stream_filter/comcast_dash/buffer/BlockBuffer.cpp)**<br />

    The BlockBuffer.cpp -


The BlockBuffer functions are:

_peek_

    The peek set a value to a pointer varaible equal to choosen point in the media.
    

_seekBackwards_

    The seekBackwards moves the pointer of the buffer to a user specified point in the media.

_get_

    The get method returns the length of the segment.
    
_put_

    The put method asigns the values to the sizeMicroSec and sizeBytes, from the block that is passed in.   

_setEOF_

    The setEOF

_getEOF_

    The getEOF
	
_attach_

    The attach
  
_notify_

    The notify notifies the bufferObservers of the new size value of the buffer.
  
_updateBufferSize_

      The updateBufferSize updates the value of the sizeMicroSec variable.

_size_

       The size returns the value of sizeMicroSec variable.
  


