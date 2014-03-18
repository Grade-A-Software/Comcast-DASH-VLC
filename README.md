##### README 

###### What is this?
The goal of this project is to create a plugin for VLC that works with Comcast's version of DASH.


###### Background
This repository holds the code and product documentation associated with a project for the Computer Science Software Engineering Practices course at Metropolitan State University of Denver. We are students developing a VLC plugin for Comcast that uses a specialized version of [DASH](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/What-is-DASH%3F). Comcast's version of DASH does not work with the current VLC DASH plugin. This repository is a clone of [VLC](https://github.com/videolan/vlc) which we use to build and test the plugin. You’ll find that most of the code here is untouched VLC. 

###### Which directory should I be looking in?
The code for the plugin exists in the [comcast_dash](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/comcast_dash) directory.<br/>
The comcast_dash directory exists in the [stream_filter](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter) directory.<br/>
The stream_filter directory is where all plugins for streaming content exists.

###### What version of VLC is this built on?
2.2.0

###### How do I build this repository?
[OSX](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-(OSX))<br/>
[Linux](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/Build-Instructions-(Linux))

###### How do I update VLC and use the plugin?
Instructions are [HERE](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki/How-do-I-update-VLC-and-use-the-plugin%3F)<br/>
Note: Functionality on future builds of VLC should work but are not guarenteed.

###### How do I run this?
From within the build directory in your command line, execute `./vlc --stream-filter comcast_dash`

###### Documentation
[Wiki](https://github.com/Grade-A-Software/Comcast-DASH-VLC/wiki)
