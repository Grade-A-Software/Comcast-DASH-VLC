#include "parser.h"

Parser::Parser(Node * root, stream_t * p_stream) :
root(root),
p_stream(p_stream)
{
}

Parser::~Parser() {}

void Parser::parse() {
    std::vector<Node *> periods = DOMHelper::getElementByTagName(this->root,"Period",false);
    for (size_t i = 0; i < periods.size(); i++) {
        Node * period = periods.at(i);
        std::vector<Node *> adaptationSet = DOMHelper::getElementByTagName(period,"AdaptationSet",false);
        for (size_t i = 0; i < adaptationSet.size(); i++) {
            std::string url = DOMHelper::getElementByTagName(adaptationSet.at(i),"BaseURL",false).at(0)->getText();
            std::vector<Node *> rep = this->getRepresentations(adaptationSet.at(i));
            std::vector<Node *> seg = this->getSegments(adaptationSet.at(i));
            if ( url.find("muxed") != std::string::npos )
                for (size_t r = 0; r < rep.size(); r++) {
                    for (size_t s = 0; s < seg.size(); s++) {
                        std::stringstream ss;
                        std::string t = seg.at(s)->getAttributeValue("t");
                        std::string rep_id = rep.at(r)->getAttributeValue("id");
                        if (seg.at(s)->getAttributeValue("r") != "0") {
                            
                            
                            char *manifestPath = p_stream->psz_path;
                            int len;
                            len = strlen( manifestPath );
                            
                            std::string pathRoot = "";
                            bool foundFirstSlash = false;
                            for (int i = len; i > -1; i--)
                            {
                                if (manifestPath[i] == '/' && !foundFirstSlash){
                                    foundFirstSlash = true;
                                    
                                }
                                if(foundFirstSlash){
                                    pathRoot = manifestPath[i] + pathRoot;
                                }
                            }
                            
                            ss << "http://" << pathRoot << url << rep_id << "-" << t << ".ts";
                            if (r == rep.size() - 1) ss << " - Highest Bit Rate - ";
                            msg_Info(this->p_stream,ss.str().c_str());
                        }
                    }
                }
        }
    }
}



std::vector<Node *> Parser::getRepresentations(Node * adaptationSet) {
    return DOMHelper::getElementByTagName(adaptationSet,"Representation",false);
}

std::vector<Node *> Parser::getSegments(Node * adaptationSet) {
    return DOMHelper::getElementByTagName(adaptationSet,"S",false);
}
