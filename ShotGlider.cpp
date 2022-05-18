#include "ShotGlider.h"
#include "BulletHandler.h"
#include "SoundManger.h"
#include "Level.h"

ShotGlider::ShotGlider() : Glider()
{
	m_bulletFiringSpeed = 70;
	m_moveSpeed = 2;
	m_gap = 30;
}

ShotGlider::~ShotGlider()
{

}

void ShotGlider::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(std::move(pParams));

	m_maxHeight = m_position.getY() + m_gap;
	m_minHeight = m_position.getY() - m_gap;

	m_velocity.setX(-m_moveSpeed);
	m_velocity.setY(m_moveSpeed / 2);
}

void ShotGlider::update()
{
	if (!m_bDying)
	{
		/*
		if (m_position.getY() >= m_maxHeight)
		{
			m_velocity.setY(-m_moveSpeed / 2);
		}
		else if (m_position.getY() <= m_minHeight)
		{
			m_velocity.setY(m_moveSpeed / 2);
		}
		*/

		//двигается на одну линию с игроком
		if (ThePlayer::Instance()->getPosition().getY() - 20 > m_position.getY())
		{
			m_velocity.setY(m_moveSpeed / 2);
		}
		else if (ThePlayer::Instance()->getPosition().getY() + 20 < m_position.getY())
		{
			m_velocity.setY(-m_moveSpeed / 2);
		}

		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 10, 16, 16, "bullet2", 1, Vector2D(-6, 0));
			TheSoundManager::Instance()->playSound("enemyshoot", 0);
			m_bulletCounter = 0;
		}
		m_bulletCounter++;
	}
	else
	{
		m_velocity.setX(0);
		doDyingAnimation();
	}
	ShooterObject::update();
}
