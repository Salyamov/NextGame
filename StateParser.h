#ifndef STATEPARSER_H
#define STATEPARSER_H

#include <iostream>
#include <vector>
#include "tinyxml.h"

class GameObject;

class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
private:
	void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTexturesIDs);
	void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
	
};

#endif
