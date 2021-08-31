#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) :
	m_tileSize(tileSize), m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize); //кол-во тайлов экрана
	m_numRows = (TheGame::Instance()->getGameHeight() / m_tileSize);
}

void TileLayer::update()
{
	m_position += m_velocity;
	m_velocity.setX(0.5);
}

void TileLayer::render()
{
	int x, y, x2, y2;

	//получаем смещение в тайлах
	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;

	//переменные чтобы отрисовка не прыгала к следующему тайлу, а отрисовывалась плавно
	x2 = int(m_position.getX()) % m_tileSize; //оставшееся пространство тайла
	y2 = int(m_position.getY()) % m_tileSize;

	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			int id = m_tileIDs[i + y][j + x]; //добавляем смещение 
			
			if (id == 0)
			{
				continue;
			}

			Tileset tileset = getTilesetByID(id); //получаем тайлсет по идентификатору

			id--;

			//отрисовывает тайл, только когда он полностью помещается на экран
			TheTextureManager::Instance()->drawTile(tileset.name, 2, 2,
				(j * m_tileSize) - x2, //пиксельная координата по x
				(i * m_tileSize) - y2, //пиксельная координата по y
				m_tileSize, m_tileSize, 
				(id - (tileset.firstGridId - 1)) / tileset.numColumns, //y (берем нужный тайл из тайлсета)
				(id - (tileset.firstGridId - 1)) % tileset.numColumns, //x
				TheGame::Instance()->getRenderer());
		}
	}
}

void TileLayer::collision()
{
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		//если больше одного тайлсета
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridId && tileID < m_tilesets[i + 1].firstGridId)
			{
				return m_tilesets[i];
			}
		}
		//если только один тайлсет (нигде больше id не найден)
		else
		{
			return m_tilesets[i];
		}
	}
	//нет тайлсетов
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;

}
