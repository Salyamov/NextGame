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
	m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);

	if (pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	{
		m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
	}

	if (!m_gameObjects.empty())
	{
		for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); )
		{
			if ((*it)->type() == std::string("ScrollingBackground"))
			{
				if (!pLevel->getTileLayerEnded())
				{
					(*it)->update();
				}
			}
			else if ((*it)->getPosition().getX() <= TheGame::Instance()->getGameWidth())
			{
				//enemies в границах экрана
				(*it)->setUpdating(true);
				(*it)->update();

			}
			else
			{
				if ((*it)->type() != std::string("Player"))
				{
					(*it)->setUpdating(false);
					(*it)->scroll(TheGame::Instance()->getScrollSpeed());
				}
				else
				{
					//игрок
					(*it)->update();
				}
			}

			//check if dead or off screen
			//(*it)->getPosition().getX() > TheGame::Instance()->getGameWidth() || (*it)->getPosition().getY() < (0 - (*it)->getHeight())
			
			//если противник залетает за левую сторону или падает ниже нижней части экрана, то он уничтожается
			if ( (*it)->getPosition().getX() < ( 0 - (*it)->getWidth() ) || 
				(*it)->getPosition().getY() > TheGame::Instance()->getGameHeight() ||
				(*it)->dead() )
			{
				delete* it;
				it = m_gameObjects.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}

void ObjectLayer::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//если объект находится в границах экрана
		if (m_gameObjects[i]->getPosition().getX() <= TheGame::Instance()->getGameWidth())
		{
			m_gameObjects[i]->draw();
		}	
	}
}


