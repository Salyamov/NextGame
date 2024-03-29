#include "Level.h"
#include "Game.h"

Level::Level() : m_bTileLayerEnded(false)
{
	TheGame::Instance()->setLevelComplete(false);
}

Level::~Level()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		delete m_layers[i];
	}
	m_layers.clear();
}

void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update(this);
	}
}

void Level::render()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}
