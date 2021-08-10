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

	//������� �� ��������� ���� <map> xml �����
	pRoot->Attribute("tilewidth", &m_tileSize); //������ ��������
	pRoot->Attribute("width", &m_width);	//������� �� ������� ��������� ��������� ������
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

	/*
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
		}
	}
	*/

	//parse objects
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers());
			}
			else if (e->FirstChildElement()->Value() == std::string("data"))
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
			}
		}
	}

	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	TheTextureManager::Instance()->load(std::string("assets/") + std::string(pTilesetRoot->FirstChildElement()->Attribute("source")),
		pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer()); //��������� ��� �������� � ��� ����� � TextureManger'�

	//��������� ��������� ��������
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width); //����� ������� ��������
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height); //������ ������� ��������
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
	TiXmlElement* pDataNode = NULL;

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
	uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size()); //����������, ������ ����������, ��������, ������ ���������

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

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"),
		TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers)
{
	ObjectLayer* pObjectLayer = new ObjectLayer();

	for (TiXmlElement* e = pObjectElement; e != NULL; e->NextSiblingElement())
	{
		if (e->Value() == std::string("object"))
		{
			int x, y, width, height, numFrames, callbackID, animSpeed;
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
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL;
						property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Value() == std::string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Value() == std::string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Value() == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Value() == std::string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (property->Value() == std::string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
						}
					}
				}
			}

			pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
			pObjectLayer->getGameObjects()->push_back(pGameObject);

		}
	}

	pLayers->push_back(pObjectLayer);

}
