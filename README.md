README 

What is this:
This repo holds the code and product documentation associated with a project for a Computer Science Software Engineering Practices course at Metropolitan State University of Denver. We are developing a VLC plugin for Comcast that uses a specialized version of DASH (link to DASH explanation page). This version of DASH does not work with the current VLC DASH plugin. This repo is a clone of [VLC](https://github.com/videolan/vlc) which we use to build and test our plugin. You’ll find that most of the code here is untouched VLC and you can find our code [HERE](https://github.com/Grade-A-Software/vlc/tree/master/modules/stream_filter/comcast_dash) which exists in the [stream_filter](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter) directory along with a modified [makefile.am](https://github.com/Grade-A-Software/Comcast-DASH-VLC/blob/master/modules/stream_filter/Makefile.am).

How to build this repo:
[OSX](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-(OSX))
[Linux](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-(Linux))

How to run:
From within the build directory, execute `./vlc --stream-filter comcast_dash`

### Documentation
[Wiki](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki).
