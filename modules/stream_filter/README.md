### You're getting close, our code is in the comcast_dash subdirectory

## Stream Filter

* Stream filter modules allow VLC to stream media from a given resource.

* The existing DASH plugin is a stream filter, and we intend to emulate the behavior of this module in our own.

### [dash/](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/dash

This directory contains the original DASH plugin that we are referencing

### [comcast_dash/](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/comcast_dash)

This directory contains _our code_. Please reference this (especially the *README*)

### Known issues with the existing DASH plugin

* Comcast's DASH Manifest (.mpd) file has a different format from traditional DASH Manifests
* Existing DASH plugin plays videos with improper timing


### Makefile.am details

* The Makefile is essential to building the module. _All source files associated with the module must be included in the SOURCES
* You must add the CXX flags
* You must add Socket libraries for HTTP streaming to work
* You must indicate the name of the object in the library

```
libcomcast_dash_plugin_la_SOURCES = \
        stream_filter/comcast_dash/dash.cpp \
        stream_filter/comcast_dash/xml/Node.h \
        stream_filter/comcast_dash/xml/Node.cpp \
        stream_filter/comcast_dash/xml/DOMParser.h \
        stream_filter/comcast_dash/xml/DOMParser.cpp \
        stream_filter/comcast_dash/xml/DOMHelper.h \
        stream_filter/comcast_dash/xml/DOMHelper.cpp
libcomcast_dash_plugin_la_CXXFLAGS = $(AM_CFLAGS) -I$(srcdir)/stream_filter/comcast_dash
libcomcast_dash_plugin_la_LIBADD = $(SOCKET_LIBS)
stream_filter_LTLIBRARIES += libcomcast_dash_plugin.la
```