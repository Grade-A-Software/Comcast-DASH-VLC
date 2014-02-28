### Stream Filter Directory

* Stream filter plugins allow VLC to stream media from a given resource.
* The [comcast_dash/](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/comcast_dash) directory contains the code for this project. The code in the folder will me modeled after the code found in the current DASH plugin directory.

* The [dash/](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/dash) directory contains the existing DASH plugin.

### Makefile.am modifications

* All source files associated with our plugin have to be included in the SOURCES
* The CXX flags are added
* The Socket libraries are added so that the HTTP streaming will work
* Indicated the name of the object in the library

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
