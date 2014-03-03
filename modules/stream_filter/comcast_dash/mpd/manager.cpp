
#import 
class Manager {

};

Manager::Manager(Node *root, stream_t *p_stream) :
  root(root),
  p_stream(p_stream)
{}

Manager::~Manager() {}

bool Manager::parse() {

  this->setAdaptationSets();
}

void Manager::setAdaptationSets(Node * period) {
  
}

void Manager::setRepresnetations(Node
