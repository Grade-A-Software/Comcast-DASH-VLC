#include "parser.h"

Parser::Parser(Node * root, stream_t * p_stream) :
root(root),
p_stream(p_stream)
{
}

Parser::~Parser() {}

MPD * Parser::parse() {
    MPD *mpd = new MPD;
    
    std::vector<Node *> periodNodes = DOMHelper::getElementByTagName(this->root,"Period",false);
    for (size_t i = 0; i < periodNodes.size(); i++) {
        Period *period = new Period;
        
        std::vector<Node *> adaptationSetNodes = DOMHelper::getElementByTagName(periodNodes.at(i),"AdaptationSet",false);
        for (size_t i = 0; i < adaptationSetNodes.size(); i++) {
            AdaptationSet *adaptationSet = new AdaptationSet;
            
            std::string directoryURL = DOMHelper::getElementByTagName(adaptationSetNodes.at(i),"BaseURL",false).at(0)->getText();
            
            //Build url from stream
            std::string baseURL = p_stream->psz_access;
            baseURL += "://";
            std::string manifestPath = p_stream->psz_path;
            size_t indexOfLastSlash = manifestPath.find_last_of( '/', manifestPath.length() - 1 );
            if ( indexOfLastSlash != std::string::npos )
                baseURL.append( manifestPath, 0, indexOfLastSlash );
            else
                baseURL += p_stream->psz_path;
            
            baseURL += '/';
            baseURL += directoryURL;
            
            std::string contentType = adaptationSetNodes.at(i)->getAttributeValue("contentType");
            std::string id = adaptationSetNodes.at(i)->getAttributeValue("id");
            
            Node * segmentTemplateNode = DOMHelper::getElementByTagName(adaptationSetNodes.at(i),"SegmentTemplate",false).at(0);
            std::string segmentTemplate = segmentTemplateNode->getAttributeValue("media");
            
            adaptationSet->setSegmentTemplate(segmentTemplate);
            adaptationSet->setBaseURL(baseURL);
            adaptationSet->setContentType(contentType);
            adaptationSet->setId(id);
            
            //Get all the representation for an adaptationSet and add each on to the adaptationSet
            std::vector<Node *> representationNodes = this->getRepresentations(adaptationSetNodes.at(i));
            for (size_t j = 0; j < representationNodes.size(); j++) {
                Representation *representation = new Representation;
                
                std::string id = representationNodes.at(j)->getAttributeValue("id");
                
                std::string bandwidthString = representationNodes.at(j)->getAttributeValue("bandwidth");
                std::string sampleRateString = representationNodes.at(j)->getAttributeValue("sampleRate");
                std::string widthString = representationNodes.at(j)->getAttributeValue("width");
                std::string heightString = representationNodes.at(j)->getAttributeValue("height");
                
                int bandwidth = atoi(bandwidthString.c_str());
                int sampleRate = atoi(sampleRateString.c_str());
                int width = atoi(widthString.c_str());
                int height = atoi(heightString.c_str());
                
                representation->setId(id);
                representation->setBandwidth(bandwidth);
                representation->setSampleRate(sampleRate);
                representation->setWidth(width);
                representation->setHeight(height);
                
                adaptationSet->addRepresentation(representation);
            }
            
            std::vector<Node *> segmentNodes = this->getSegments(adaptationSetNodes.at(i));
            for (size_t j = 0; j < segmentNodes.size(); j++) {
                Segment *segment = new Segment;
                
                std::string timeString = segmentNodes.at(j)->getAttributeValue("t");
                std::string durationString = segmentNodes.at(j)->getAttributeValue("d");
                std::string repeatString = segmentNodes.at(j)->getAttributeValue("r");
                
                int time = atoi(timeString.c_str());
                int duration = atoi(durationString.c_str());
                int repeat = atoi(repeatString.c_str());
                
                segment->setTime(time);
                segment->setDuration(duration);
                segment->setRepeat(repeat);
                
                adaptationSet->addSegment(segment);
            }
            
            period->addAdaptationSet(adaptationSet);
        }
        mpd->addPeriod(period);
    }
    return mpd;
}



std::vector<Node *> Parser::getRepresentations(Node * adaptationSet) {
    return DOMHelper::getElementByTagName(adaptationSet,"Representation",false);
}

std::vector<Node *> Parser::getSegments(Node * adaptationSet) {
    return DOMHelper::getElementByTagName(adaptationSet,"S",false);
}
