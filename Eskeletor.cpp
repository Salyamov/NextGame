#include "Eskeletor.h"
#include "Game.h"
#include "BulletHandler.h"
#include "SoundManger.h"

Eskeletor::Eskeletor() : Enemy()
{
	m_dyingTime = 25;
	m_health = 3;
	m_maxHealth = 3;
	m_moveSpeed = 1;
	m_bulletFiringSpeed = 100;

	m_velocity.setY(1);
}

Eskeletor::~Eskeletor()
{
}

void Eskeletor::update()
{
	if (!m_bDying)
	{
		GameObject::scroll(TheGame::Instance()->getScrollSpeed());


		if (m_position.getY() >= TheGame::Instance()->getGameHeight() - m_height - 32)
		{
			m_velocity.setY(-m_moveSpeed);
		}
		else if (m_position.getY() <= 0 + 32)
		{
			m_velocity.setY(m_moveSpeed);
		}
		
		
		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-3, 0));
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(3, 0));
			m_bulletCounter = 0;
		}
		m_bulletCounter++;
		m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
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
	
	m_health -= 1;

	m_alpha = ((float)m_health / (float)m_maxHealth) * 255;	

	if (m_health == 0)
	{
		if (!m_bPlayedDeathSound)
		{
			TheSoundManager::Instance()->playSound("explode", 0);
			m_textureID = "largeexplosion";
			m_alpha = 255;
			m_currentFrame = 0;
			m_numFrames = 9;
			m_width = 60;
			m_height = 60;
			m_bDying = true;
			TheGame::Instance()->addToGameScore(400);
		}
	}


	
}
