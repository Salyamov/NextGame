#include "Turret.h"
#include "Game.h"
#include "BulletHandler.h"

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
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet2", 1, Vector2D(-3, -3));
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -3));
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(3, -3));
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
