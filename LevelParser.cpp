#include "LevelParser.h"
#include "base64.h"
#include "TileLayer.h"
#include "TextureManager.h"
#include "Game.h"

#include "zlib.h"
#include "zconf.h"


Level* LevelParser::parseLevel(const char* levelFile)
{
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	Level* pLevel = new Level();

	TiXmlElement* pRoot = levelDocument.RootElement();

	//берутся из корневого тега <map> xml файла
	pRoot->Attribute("tilewidth", &m_tileSize); //размер квадрата
	pRoot->Attribute("width", &m_width);	//сколько на сколько квадратов
	pRoot->Attribute("height", &m_height);  

	//parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); pRoot != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	//parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); pRoot != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
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
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

	std::vector< std::vector<int> > data;
	
	std::string decodedIDs;
	TiXmlElement* pDataNode;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	//uncompress zlib compression
	uLongf sizeofids = m_width * m_height * sizeof(int);
	std::vector<int> ids(m_width * m_height);
	uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size()); //назначение, размер назначения, источник, размер источника

	std::vector<int> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = ids[rows * m_width + cols];
		}
	}

	pTileLayer->setTileIDs(data);
	pLayers->push_back(pTileLayer);

}