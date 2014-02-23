##### README 

###### What is this?
This repo holds the code and product documentation associated with a project for the Computer Science Software Engineering Practices course at Metropolitan State University of Denver. We are developing a VLC plugin for Comcast that uses a specialized version of [DASH](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/What-is-DASH%3F). This version of DASH does not work with the current VLC DASH plugin. This repo is a clone of [VLC](https://github.com/videolan/vlc) which we use to build and test our plugin. You’ll find that most of the code here is untouched VLC. Our plugin code is  [HERE](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/comcast_dash). This code exists in the [stream_filter](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter) directory.

###### How do I build this repo?
[OSX](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-(OSX))<br/>
[Linux](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-(Linux))

###### How do I run this?
From within the build directory in your command line, execute `./vlc --stream-filter comcast_dash`

###### Documentation
[Wiki](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki)
