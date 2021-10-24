#include "BossHelicopter.h"
#include "Game.h"
#include "SoundManger.h"
#include "BulletHandler.h"

BossHelicopter::BossHelicopter()
{
	m_health = 10;
	m_dyingTime = 50;
	m_hitTimer = 0;
	m_tickCounter = 0;
	m_maxTicks = 25;
	m_moveSpeed = 2;
	m_bMoovingUp = false;
	m_bMoovingDown = false;
	m_bulletCounter = 0;
	m_bulletFiringSpeed = 50;
	m_bulletSpeed = 4;
}

BossHelicopter::~BossHelicopter()
{
}

void BossHelicopter::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void BossHelicopter::update()
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

		float delta = std::sqrt(x*x + y*y) * (1/m_bulletSpeed);

		x /= delta;
		y /= delta;
		Vector2D heading(x, y);

		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + m_height / 2, 16, 16, "bullet2", 1,
				//ThePlayer::Instance()->getPosition());
				heading);
			TheSoundManager::Instance()->playSound("enemyshoot", 0);
			m_bulletCounter = 0;
		}
		m_bulletCounter++;

		//уворот от выстрела

		//если находится на линии огня игрока и игрок стреляет
		if (ThePlayer::Instance()->getPlayerShot() && 
			((bossTop < playerTop && bossBot > playerTop ) || (bossTop < playerBot && bossBot > playerBot )) &&
			!m_bMoovingDown && !m_bMoovingUp)
		{
			//тут надо добавить уворот вверх или вниз
			
			//определяем в какую сторону ближе
			if (std::abs(playerCenter - bossTop) > std::abs(playerCenter - bossBot))
			{
				//вверх
				
				//если достаточно места вверху
				if (bossTop - m_moveSpeed * m_maxTicks > 0)
				{
					m_bMoovingUp = true;
				}
				else
				{
					m_bMoovingDown = true;
				}
			}
			else
			{
				//вниз

				//если достаточно места внизу
				if (bossBot + m_moveSpeed * m_maxTicks < TheGame::Instance()->getGameHeight() - 32)
				{
					m_bMoovingDown = true;
				}
				else
				{
					m_bMoovingUp = true;
				}
			}
			
		}
		else if (m_bMoovingUp == true)
		{
			m_velocity.setY(-m_moveSpeed);
			m_tickCounter++;
			if (m_tickCounter >= m_maxTicks)
			{
				m_bMoovingUp = false;
				m_tickCounter = 0;
			}
		}
		else if (m_bMoovingDown == true)
		{
			m_velocity.setY(m_moveSpeed);
			m_tickCounter++;
			if (m_tickCounter >= m_maxTicks)
			{
				m_bMoovingDown = false;
				m_tickCounter = 0;
			}
		}
		else
		{
			m_velocity.setX(0);
			m_velocity.setY(0);
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

void BossHelicopter::collision()
{
	m_health -= 1;

	m_bHitted = true;

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
			TheGame::Instance()->addToGameScore(2000);

		}
	}
}
