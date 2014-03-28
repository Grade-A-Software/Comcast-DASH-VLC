#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "HTTPConnectionManager.h"
#include "mpd/Segment.h"

using namespace comcast_dash::http;
using namespace comcast_dash::mpd;

const size_t    HTTPConnectionManager::PIPELINE               = 80;
const size_t    HTTPConnectionManager::PIPELINELENGTH         = 2;
const uint64_t  HTTPConnectionManager::CHUNKDEFAULTBITRATE    = 1;

HTTPConnectionManager::HTTPConnectionManager    (MPD *mpd, stream_t *stream) :
                       mpd     (mpd),
                       stream                   (stream),
                       chunkCount               (0),
                       bpsAvg                   (0),
                       bpsLastChunk             (0),
                       bpsCurrentChunk          (0),
                       bytesReadSession         (0),
                       bytesReadChunk           (0),
                       timeSession              (0),
                       timeChunk                (0)
{
  std::stringstream ss;
  ss << &stream;
  msg_Info(stream,ss.str().c_str());
  msg_Info(stream,"^ Original");
  std::stringstream ss2;
  ss2 << &(this->stream);
  msg_Info(stream,ss2.str().c_str());
  msg_Info(stream,"^ Class"); 
  std::stringstream ss3;
  //  ss3 << net_ConnectTCP(this->stream,"nh.lab.xcal.tv",80);
  msg_Info(stream,ss3.str().c_str());
  msg_Info(stream,"^ Works"); 
}
HTTPConnectionManager::~HTTPConnectionManager   ()
{
    this->closeAllConnections();
}

void                                HTTPConnectionManager::closeAllConnections      ()
{
    vlc_delete_all(this->connectionPool);
    vlc_delete_all(this->downloadQueue);
}
int                                 HTTPConnectionManager::read                     (block_t *block)
{
  /*  msg_Info(this->stream,"Reading");
   */

  /*  msg_Info(stream,"^ Class2"); 
  std::stringstream ss3;
  ss3 << net_ConnectTCP(this->stream,"nh.lab.xcal.tv",80);
  msg_Info(stream,ss3.str().c_str());
  msg_Info(stream,"^ Works2"); 
  */
  std::stringstream ss1;
  ss1 << (this->mpd->getNextChunk()->getUrl()) << " <- true";
  msg_Info(stream,ss1.str().c_str());

    if(this->downloadQueue.size() == 0)
       if(!this->addChunk(this->mpd->getNextChunk()))
            return 0;
  std::stringstream ss2;
  ss2 << this->downloadQueue.size() << " <- size";
  msg_Info(stream,ss2.str().c_str());
    if(this->downloadQueue.front()->getPercentDownloaded() > HTTPConnectionManager::PIPELINE &&
       this->downloadQueue.size() < HTTPConnectionManager::PIPELINELENGTH)
       this->addChunk(this->mpd->getNextChunk());

    int ret = 0;

    mtime_t start = mdate();
    ret = this->downloadQueue.front()->getConnection()->read(block->p_buffer, block->i_buffer);
    mtime_t end = mdate();

    block->i_length = (mtime_t)((ret * 8) / ((float)this->downloadQueue.front()->getBitrate() / 1000000));

    double time = ((double)(end - start)) / 1000000;

    if(ret <= 0)
    {
        this->bpsLastChunk   = this->bpsCurrentChunk;
        this->bytesReadChunk = 0;
        this->timeChunk      = 0;

        delete(this->downloadQueue.front());
        this->downloadQueue.pop_front();

        return this->read(block);
    }
    else
    {
        this->updateStatistics(ret, time);
    }

    return ret;
}

std::vector<PersistentConnection *> HTTPConnectionManager::getConnectionsForHost    (const std::string &hostname)
{
    std::vector<PersistentConnection *> cons;

    for(size_t i = 0; i < this->connectionPool.size(); i++)
        if(!this->connectionPool.at(i)->getHostname().compare(hostname) || !this->connectionPool.at(i)->isConnected())
            cons.push_back(this->connectionPool.at(i));

    return cons;
}
void                                HTTPConnectionManager::updateStatistics         (int bytes, double time)
{
    this->bytesReadSession  += bytes;
    this->bytesReadChunk    += bytes;
    this->timeSession       += time;
    this->timeChunk         += time;

    this->bpsAvg            = (int64_t) ((this->bytesReadSession * 8) / this->timeSession);
    this->bpsCurrentChunk   = (int64_t) ((this->bytesReadChunk * 8) / this->timeChunk);

    if(this->bpsAvg < 0)
        this->bpsAvg = 0;

    if(this->bpsCurrentChunk < 0)
        this->bpsCurrentChunk = 0;

}
bool                                HTTPConnectionManager::addChunk                 (Chunk *chunk)
{

    if(chunk == NULL)
        return false;
    std::stringstream ss;
    ss << &(this->stream); //"adding chunk " << chunk->getUrl();
    msg_Info(this->stream,ss.str().c_str());
    this->downloadQueue.push_back(chunk);
    msg_Info(this->stream,"test");   
    std::vector<PersistentConnection *> cons = this->getConnectionsForHost(chunk->getHostname());
   msg_Info(this->stream,"tes2");
   if(cons.size() == 0)
     {   msg_Info(this->stream,"test3");
        PersistentConnection *con = new PersistentConnection(this->stream);
        this->connectionPool.push_back(con);
        cons.push_back(con);
	msg_Info(this->stream,"test4");
     }

    size_t pos = this->chunkCount % cons.size();
 
    cons.at(pos)->addChunk(chunk);
    msg_Info(this->stream,"Chunk aaaaaaaaah");
    chunk->setConnection(cons.at(pos));

    this->chunkCount++;

    if(chunk->getBitrate() <= 0)
        chunk->setBitrate(HTTPConnectionManager::CHUNKDEFAULTBITRATE);
    std::stringstream ss2;
    ss2 << this->chunkCount << "chunks";
    msg_Info(this->stream,ss2.str().c_str());
    return true;

}
