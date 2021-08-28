#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include "Layer.h"
#include "Player.h"

struct Tileset
{
	int firstGridId;
	int tileWidth; //длина отдельного тайла
	int tileHeight; //ширина отдельного тайла
	int spacing;
	int margin;
	int width; //длина тайлсета
	int height; //ширина тайлсета
	int numColumns;
	std::string name;
};

class Level
{
	friend class LevelParser;

public:

	~Level();

	void update();
	void render();

	std::vector<Tileset>* getTilesets()	{ return &m_tilesets; }
	std::vector<Layer*>* getLayers() { return &m_layers; }
	std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }

	Player* getPlayer() { return m_pPlayer; }
	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:
	Level();

	Player* m_pPlayer;

	std::vector<Tileset> m_tilesets; 
	std::vector<Layer*> m_layers;
	std::vector<TileLayer*> m_collisionLayers;

};



























#endif