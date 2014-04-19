#### **HTTP connections and downloading**

**HTTPConnectionManager**
- This object manages all of the connections and downloader objects that its parent (DASHDownloader) requires.

**HTTPConnection**
- Basic http connection, inherits from virtual class IHTTPConnection

**PersistentConnection**
- Http connection that will pass several requests rather than just a single one

**IHTTPConnection**
- Virtual class to provide framework for HTTPConnection and PersistentConnection by extension

**Chunk**
- A container object for a segment of bytes downloaded by a PersistentConnection
