#include "BulletHandler.h"
#include "Game.h"

BulletHandler* BulletHandler::s_pInstance = new BulletHandler();

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{
	PlayerBullet* pPlayerBullet = new PlayerBullet();
	pPlayerBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);
	m_playerBullets.push_back(pPlayerBullet);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{
	EnemyBullet* pEnemyBullet = new EnemyBullet();
	pEnemyBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);
	m_enemyBullets.push_back(pEnemyBullet);
}

void BulletHandler::updateBullets()
{
	for (std::vector<EnemyBullet*>::iterator p_it = m_enemyBullets.begin(); p_it != m_enemyBullets.end(); )
	{
		if ((*p_it)->getPosition().getX() < 0 || (*p_it)->getPosition().getX() > TheGame::Instance()->getGameWidth() ||
			(*p_it)->getPosition().getY() < 0 || (*p_it)->getPosition().getY() > TheGame::Instance()->getGameHeight())
		{
			delete *p_it;//delete bullet
			p_it = m_enemyBullets.erase(p_it); //remove empty space and return iterator to next element
		}
		else
		{
			(*p_it)->update();
			p_it++;
		}
	}

	for (std::vector<PlayerBullet*>::iterator p_it = m_playerBullets.begin(); p_it != m_playerBullets.end(); )
	{
		if ((*p_it)->getPosition().getX() < 0 || (*p_it)->getPosition().getX() > TheGame::Instance()->getGameWidth() ||
			(*p_it)->getPosition().getY() < 0 || (*p_it)->getPosition().getY() > TheGame::Instance()->getGameHeight())
		{
			delete* p_it;
			p_it = m_playerBullets.erase(p_it);
		}
		else
		{
			(*p_it)->update();
			p_it++;
		}
	}
}

void BulletHandler::drawBullets()
{
	for (int i = 0; i < m_enemyBullets.size(); i++)
	{
		m_enemyBullets[i]->draw();
	}

	for (int i = 0; i < m_playerBullets.size(); i++)
	{
		m_playerBullets[i]->draw();
	}

}

void BulletHandler::clearBullets()
{
	m_playerBullets.clear();
	m_enemyBullets.clear();
}

void BulletHandler::deleteBullet(PlayerBullet* bullet)
{
	for (std::vector<PlayerBullet*>::iterator p_it = m_playerBullets.begin(); p_it != m_playerBullets.end(); )
	{
		if ((*p_it) == bullet)
		{
			delete *p_it;
			p_it = m_playerBullets.erase(p_it);
		}
		else
		{
			p_it++;
		}
	}
	//m_playerBullets.erase()
	//delete
}

BulletHandler::BulletHandler()
{
}

BulletHandler::~BulletHandler()
{
}
