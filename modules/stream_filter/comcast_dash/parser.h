#include "xml/Node.h"
#include "xml/DOMParser.h"
#include "xml/DOMHelper.h"
#include <cstdlib>
#include <sstream>


using namespace dash;
using namespace dash::xml;

class Parser {
 public:
  Node * root;
  stream_t * p_stream;
  std::vector<Node *> periods;
  Parser(Node * root, stream_t * p_stream);
  virtual ~Parser();
  void parse();

  std::vector<Node *> getRepresentations(Node *);
  std::vector<Node *> getSegments(Node *);
  void print();
};
