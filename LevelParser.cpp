#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"

Level* LevelParser::parseLevel(const char* levelFile)
{
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	Level* pLevel = new Level();

	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	//parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); pRoot != NULL; e = pRoot->NextSiblingElement())
	{
		if (e->Value() == "tileset")
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	//parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); pRoot != NULL; e = pRoot->NextSiblingElement())
	{
		if (e->Value() == "layer")
		{
			parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
		}
	}

	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"),
		pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer()); //сохраняем имя тайлсета и его адрес в TextureManger'е

	//сохраняем параметры тайлсета
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width); //длина рисунка тайлсета
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height); //ширина рисунка тайлсета
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridId);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");

	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets)
{

}