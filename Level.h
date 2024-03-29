#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include "Layer.h"
#include "Player.h"

class TileLayer;

struct Tileset
{
	int firstGridId;
	int tileWidth; //����� ���������� �����
	int tileHeight; //������ ���������� �����
	int spacing;
	int margin;
	int width; //����� ��������
	int height; //������ ��������
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
	std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; } //������ ������ �� ������ ���������� �� ����������

	const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; } //������ ���������(�����)

	Player* getPlayer() { return m_pPlayer; }
	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	//����������� �� ��������� ����� � TileLayer
	bool getTileLayerEnded() { return m_bTileLayerEnded; }
	void setTileLayerEnded(bool ended) { m_bTileLayerEnded = ended; }

private:
	Level();

	Player* m_pPlayer;
	bool m_bTileLayerEnded;

	std::vector<Tileset> m_tilesets; 
	std::vector<Layer*> m_layers;
	std::vector<TileLayer*> m_collisionLayers;

};



























#endif