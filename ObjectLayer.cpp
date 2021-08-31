#include "ObjectLayer.h"
#include "Level.h"
#include "Game.h"

ObjectLayer::~ObjectLayer()
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete* it;
	}
	m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
	m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
	m_collisionManager.checkEnemyPlayerBulletCollision((std::vector<GameObject*>&)m_gameObjects);
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (std::vector<GameObject*>&)m_gameObjects);

	if (pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	{
		m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
	}






	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void ObjectLayer::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}


