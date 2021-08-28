#include "LevelParser.h"
#include "base64.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
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
	TiXmlElement* pProperties = pRoot->FirstChildElement();

	//берутся из корневого тега <map> xml файла
	pRoot->Attribute("tilewidth", &m_tileSize); //размер квадрата
	pRoot->Attribute("width", &m_width);	//сколько на сколько квадратов двумерный массив
	pRoot->Attribute("height", &m_height);  

	//parse textures
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			parseTextures(e);
		}
	}

	//parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	//parse objects
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers(), pLevel);
			}
			else if (e->FirstChildElement()->Value() == std::string("data") ||
				(e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"))) //if <properties> before <data>
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers());
			}
		}
	}

	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	TheTextureManager::Instance()->load(std::string("assets/") + std::string(pTilesetRoot->FirstChildElement()->Attribute("source")),
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

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*>* pCollisionLayers)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

	bool collidable = false;

	std::vector< std::vector<int> > data;
	
	std::string decodedIDs;
	TiXmlElement* pDataNode = NULL;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* prop = e->FirstChildElement(); prop != NULL; prop = prop->NextSiblingElement())
			{
				if (prop->Value() == std::string("property"))
				{
					if (prop->Attribute("name") == std::string("collidable"))
					{
						collidable = true;
					}
				}
			}
		}

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

	if (collidable)
	{
		pCollisionLayers->push_back(collidable);
	}

	pLayers->push_back(pTileLayer);

}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"),
		TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel)
{
	ObjectLayer* pObjectLayer = new ObjectLayer();

	std::cout << pObjectElement->FirstChildElement()->Value();

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::cout << e->Value();
		if (e->Value() == std::string("object"))
		{
			int x, y, width, height, numFrames, callbackID = 0, animSpeed = 0;
			std::string textureID;

			e->Attribute("x", &x);
			e->Attribute("y", &y);

			GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));

			//property values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL;
				properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* prop = properties->FirstChildElement(); prop != NULL;
						prop = prop->NextSiblingElement())
					{
						if (prop->Value() == std::string("property"))
						{
							if (prop->Attribute("name") == std::string("numFrames"))
							{
								prop->Attribute("value", &numFrames);
							}
							else if (prop->Attribute("name") == std::string("textureWidth"))
							{
								prop->Attribute("value", &width);
							}
							else if (prop->Attribute("name") == std::string("textureHeight"))
							{
								prop->Attribute("value", &height);
							}
							else if (prop->Attribute("name") == std::string("textureID"))
							{
								textureID = prop->Attribute("value");
							}
							else if (prop->Attribute("name") == std::string("callbackID"))
							{
								prop->Attribute("value", &callbackID);
							}
							else if (prop->Attribute("name") == std::string("animSpeed"))
							{
								prop->Attribute("value", &animSpeed);
							}
						}
					}
				}
			}

			pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
			
			if (pGameObject->type() == "Player")
			{
				pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
			}

			pObjectLayer->getGameObjects()->push_back(pGameObject);

		}
	}

	pLayers->push_back(pObjectLayer);

}
