#include "Turret.h"
#include "Game.h"

Turret::Turret()
{
	m_dyingTime = 1000;
	m_health = 15;
	m_bulletFiringSpeed = 50;
}

Turret::~Turret()
{
}

void Turret::update()
{
	if (!m_bDying)
	{
		scroll(TheGame::Instance()->getScrollSpeed());

		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet();
			TheBulletHandler::Instance()->addEnemyBullet();
			TheBulletHandler::Instance()->addEnemyBullet();
			m_bulletCounter = 0;
		}
		m_bulletCounter++;
	}
	else
	{
		scroll(TheGame::Instance()->getScrollSpeed());
		doDyingAnimation();
	}
}
