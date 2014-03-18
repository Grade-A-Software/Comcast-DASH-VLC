#include "xml/Node.h"
#include "xml/DOMParser.h"
#include "xml/DOMHelper.h"
#include "mpd/MPD.h"
#include "mpd/AdaptationSet.h"
#include "mpd/Period.h"
#include "mpd/Representation.h"
#include "mpd/Segment.h"
#include <cstdlib>
#include <sstream>


using namespace comcast_dash;
using namespace comcast_dash::xml;
using namespace comcast_dash::mpd;

class Parser {
public:
    Node * root;
    stream_t * p_stream;
    std::vector<Node *> periods;
    Parser(Node * root, stream_t * p_stream);
    virtual ~Parser();
    MPD * parse();
    
    std::vector<Node *> getRepresentations(Node *);
    std::vector<Node *> getSegments(Node *);
};
