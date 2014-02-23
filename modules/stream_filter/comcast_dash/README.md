### Comcast DASH plugin


**Plugin Creation**<br />
Information for how we created this plugin can be found [HERE](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Module-Creation)
<br />
<br />
**Plugin Logic**<br />
An overview of the process this plugin will follow can be found [HERE](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Playback-Loop-Logic)



**hello.c**<br />

This is a demonstration of how a module will be loaded. This is trivial, and should be used only for reference.

**dash.cpp**<br />

This is the module. Contained is the module definition, and essential methods for plugin creation.

**dash.cpp - functions**<br />

_Open_

	Open is invoked when the module loads. Initializes system information and parses the XML
_Close_

	Frees memory and ends execution.
_Read_

	_Not currently implemented_

	Will ultimately read a chunk of data from the server

_Peek_

	_Not currently implmemented_

	Will ultimately allow the user to peek to a specific point in the video.

_Control_

	_Not currently implemented_

	Will ultimately represent control choices in the VLC interface.
