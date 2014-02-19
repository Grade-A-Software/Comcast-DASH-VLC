Comcast VLC DASH Plugin
===============
Grade A Software
================

### How to Run the Code

First, check out the source code for our version of VLC from `git clone https://github.com/Grade-A-Software/Comcast-DASH-VLC.git`

Then build [(OSX)](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-%28OSX%29),[(Linux)](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-%28Linux%29) the project and the plugin will be in the build directory.

Finally, from within the build directory, execute `./vlc --stream-filter comcast_dash`

### Our code is [right here](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter). PLEASE scroll down to read the README.md file for a breakdown of code.

### We are referencing [this](https://github.com/Grade-A-Software/vlc/tree/master/modules/stream_filter/dash) portion of the VLC codebase as a model for using DASH with VLC.

_We have not identified why this does not work for Comcast_

Welcome to the project GitHub repository!

### We do [SCRUM!](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Scrum-Process)


### User Stories

*User stories are on [Rally](https://rally1.rallydev.com).* 
_You will need to log in to view this_

### Documentation

* _PLEASE_ read the README.md files in the [root directory](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/README.md), the [modules/stream_filter directory](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/README.md), and the [modules/stream_filter/comcast_dash](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/comcast_dash/README.md) directory
* For full documentation of project requirements, architecture, design, and code available on the [Wiki](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki).
