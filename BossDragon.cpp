#include "BossDragon.h"
#include "Game.h"
#include "BulletHandler.h"
#include "SoundManger.h"

BossDragon::BossDragon()
{
	m_health = 7;
	m_moveSpeed = 2;
	m_bulletCounter = 0;
	m_bulletSpeed = 6;
	m_bulletFiringSpeed = 15;

	m_firingCountdownCounter = 0;
	m_firingCountdown = 100;

	m_firingDurationCounter= 0;
	m_firingDuration = 75;

	m_bHitted = false;
	m_hitTimer = 0;
	
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
			m_bFiring = true;

			if (m_bulletCounter == m_bulletFiringSpeed)
			{
				TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + m_height / 2, 32, 32, "bullet3", 1, heading);
				TheSoundManager::Instance()->playSound("dragonbreath", 0);
				m_bulletCounter = 0;

			}
			m_bulletCounter++;

		}
		else if(m_firingDurationCounter < m_firingDuration)
		{
			m_firingDurationCounter++;
			m_bFiring = false;
			
		}
		else
		{
			m_firingDurationCounter = 0;
			m_firingCountdownCounter = 0;
			
		}

		if (m_bFiring)
		{
			m_currentFrame = 4;
			m_numFrames = 1;
		}
		else
		{
			m_numFrames = 3;
		}

		m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
		ShooterObject::update();

		//отображение попаданий
		if (m_bHitted == true)
		{
			m_alpha = 100;
			m_bHitted = false;
			m_hitTimer = 0;
		}
		else
		{
			if (m_hitTimer == 5)
			{
				m_alpha = 255;
			}
			m_hitTimer++;
		}


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
	m_health -= 1;

	m_bHitted = true;

	if (m_health == 0)
	{
		/*
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
			TheGame::Instance()->addToGameScore(2000);

		}
		*/

		TheSoundManager::Instance()->playSound("dragondeath", 0);

		m_bDying = true;
		TheGame::Instance()->addToGameScore(2000);
	}
}
