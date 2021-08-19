#include "ShotGlider.h"

ShotGlider::ShotGlider() : m_bulletFiringSpeed(25), m_moveSpeed(3)
{

}

ShotGlider::~ShotGlider()
{

}

void ShotGlider::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
	m_velocity.setX(-m_moveSpeed);
}

void ShotGlider::update()
{
	if (!m_bDying)
	{
		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet();
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
