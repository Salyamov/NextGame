#ifndef TILELAYER_H
#define TILELAYER_H
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"
#include <vector>

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
	virtual void update();
	virtual void render();

	void setTileIDs(const std::vector< std::vector<int> >& data)
	{
		m_tileIDs = data;
	}

	void setTileSize(int tileSize)
	{
		m_tileSize = tileSize;
	}

	Tileset getTilesetByID(int tileID);

private:

	int m_tileSize;
	int m_numColumns; //кол-во отображаемых столбцов
	int m_numRows; //кол-вл отображаемых строк

	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset>& m_tilesets;
	std::vector< std::vector<int> > m_tileIDs; //двумерный массив идентификаторов тайлов

};



























#endif
