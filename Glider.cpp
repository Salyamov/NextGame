#include "Glider.h"

Glider::Glider() : Enemy()
{
	m_dyingTime = 25;
	m_health = 1;
	m_moveSpeed = 3;
	m_gap = 60;
}

Glider::~Glider()
{
}

void Glider::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(std::move(pParams));

	m_velocity.setX(-m_moveSpeed);
	m_velocity.setY(m_moveSpeed / 2);

	m_maxHeight = m_position.getY() + m_gap;
	m_minHeight = m_position.getY() - m_gap;
}

void Glider::update()
{
	if (!m_bDying)
	{
		if (m_position.getY() >= m_maxHeight)
		{
			m_velocity.setY(-m_moveSpeed);
		}
		else if (m_position.getY() <= m_minHeight)
		{
			m_velocity.setY(m_moveSpeed);
		}
	}
	else
	{
		m_velocity.setX(0);
		m_velocity.setY(0);
		doDyingAnimation();
	}

	ShooterObject::update();
}

void Glider::collision()
{
}

