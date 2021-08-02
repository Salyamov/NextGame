#include "TileLayer.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) :
	m_tileSize(tileSize), m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	
}

void TileLayer::update()
{
}

void TileLayer::render()
{
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	return Tileset();
}
