##Comcast DASH plugin

*Details:*

**Module Creation**<br />
Information for creating a module can be found at:<br /> 
[Walk-through for Module Creation](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Module-Creation)
<br />
<br />
**Playback Loop**<br />
An overview of the playback loop can be found at:<br />
[Playback Loop Logic](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Playback-Loop-Logic)


### Consult README files in appropriate subdirectories for details on those components

### hello.c

This is a demonstration of how a module will be loaded. This is trivial, and should be used only for reference.

### dash.cpp

This is the module. Contained is the module definition, and essential methods for plugin creation.

### dash.cpp - functions

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
