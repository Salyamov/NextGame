#include "Eskeletor.h"
#include "Game.h"

Eskeletor::Eskeletor() : Enemy()
{
	m_dyingTime = 50;
	m_health = 3;
	m_moveSpeed = 3;
	m_bulletFiringSpeed = 50;
}

Eskeletor::~Eskeletor()
{
}

void Eskeletor::update()
{
	if (!m_bDying)
	{
		scroll(TheGame::Instance()->getScrollSpeed());
		m_velocity.setY(m_moveSpeed);
		
		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet();
			TheBulletHandler::Instance()->addEnemyBullet();
		}
		m_bulletCounter++;
	}
	else
	{
		m_velocity.setY(0);
		doDyingAnimation();
	}
	ShooterObject::update();
}

void Eskeletor::collision()
{
}
