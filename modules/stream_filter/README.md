### Stream Filter Directory

* Stream filter plugins allow VLC to stream media from a given resource.
 
##### Content associated with the plugin:
* The [comcast_dash/](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/comcast_dash) directory contains the code for this project. The code in this folder will be modeled after the code found in the current DASH plugin directory.

* The [dash/](https://github.com/Grade-A-Software/Comcast-DASH-VLC/tree/master/modules/stream_filter/dash) directory contains the existing DASH plugin.

* The [Makefile.am](https://github.com/Grade-A-Software/Comcast-DASH-VLC/blob/master/modules/stream_filter/Makefile.am) file is lists all the files associated with a given plugin. 


##### Makefile.am modifications
The modifcation made so far is the addition of these lines:

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

* `libcomcast_dash_plugin_la_SOURCES` - source files associated with the plugin
* `libcomcast_dash_plugin_la_CXXFLAGS = $(AM_CFLAGS) -I$(srcdir)/stream_filter/comcast_dash` - CXX flags
* `libcomcast_dash_plugin_la_LIBADD = $(SOCKET_LIBS)` - (Socket libraries) added so that the HTTP streaming will work
