#include "BossDragon.h"
#include "Game.h"
#include "BulletHandler.h"
#include "SoundManger.h"

BossDragon::BossDragon()
{
	m_health = 10;
	m_moveSpeed = 2;
	m_bulletCounter = 0;
	m_bulletSpeed = 1;
	m_bulletFiringSpeed = 20;

	m_firingCountdownCounter = 0;
	m_firingCountdown = 100;

	m_firingDurationCounter= 0;
	m_firingDuration = 100;
	
}

void BossDragon::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void BossDragon::update()
{
	if (!m_bDying)
	{
		int playerTop = ThePlayer::Instance()->getPosition().getY();
		int playerBot = ThePlayer::Instance()->getPosition().getY() + ThePlayer::Instance()->getHeight();
		int playerFront = ThePlayer::Instance()->getPosition().getX() + ThePlayer::Instance()->getWidth();
		int bossFront = m_position.getX();
		int bossTop = m_position.getY();
		int bossBot = m_position.getY() + m_height;
		int playerHeight = ThePlayer::Instance()->getHeight();
		int playerCenter = playerTop + playerHeight / 2;
		int bossCenter = bossTop + m_height / 2;

		//выстрел

		float x = playerFront - bossFront;
		float y = playerCenter - bossCenter;

		float delta = std::sqrt(x * x + y * y) * (1 / m_bulletSpeed);

		x /= delta;
		y /= delta;
		Vector2D heading(x, y);

		if (m_firingCountdownCounter < m_firingCountdown)
		{
			m_firingCountdownCounter++;
			

			if (m_bulletCounter == m_bulletFiringSpeed)
			{
				TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + m_height / 2, 32, 32, "bullet3", 1, heading);
				//TheSoundManager::Instance()->playSound("enemyshoot", 0);
				m_bulletCounter = 0;

			}
			m_bulletCounter++;

		}
		else if(m_firingDurationCounter < m_firingDuration)
		{
			m_firingDurationCounter++;
			
		}
		else
		{
			m_firingDurationCounter = 0;
			m_firingCountdownCounter = 0;
		}


		m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
		ShooterObject::update();

		//если уровень не закончен, то скроллим
		if (!TheGame::Instance()->getLevelComplete())
		{
			scroll(TheGame::Instance()->getScrollSpeed());
		}
	}

	else
	{
		m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % m_numFrames);

		if (m_dyingCounter == m_dyingTime)
		{
			m_bDead = true;
			ThePlayer::Instance()->setBossIsDead(true);
		}
		m_dyingCounter++;

	}
}

void BossDragon::collision()
{
}
