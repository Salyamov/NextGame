#include "BossHelicopter.h"
#include "Game.h"
#include "SoundManger.h"

BossHelicopter::BossHelicopter()
{
	m_health = 20;
	m_dyingTime = 50;
	m_hitTimer = 0;
	m_tickCounter = 0;
	m_maxTicks = 5;
	m_moveSpeed = 1;
	m_bMooving = false;
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
		int playerTopY = ThePlayer::Instance()->getPosition().getY();
		int playerBotY = ThePlayer::Instance()->getPosition().getY() + ThePlayer::Instance()->getHeight();
		int bossTopY = m_position.getY();
		int bossBotY = m_position.getY() + m_height;
		int playerHeight = ThePlayer::Instance()->getHeight();
		int playerCenter = playerTopY + playerHeight / 2;

		//если находится на линии огня игрока и игрок стреляет
		if (ThePlayer::Instance()->getPlayerShot() && 
			((bossTopY < playerTopY && bossBotY > playerTopY ) || (bossTopY < playerBotY && bossBotY > playerBotY ))
			)
			/*
			((m_position.getY() > ThePlayer::Instance()->getPosition().getY() &&
				m_position.getY() + m_height < ThePlayer::Instance()->getPosition().getY()) ||
				(m_position.getY() + m_height > ThePlayer::Instance()->getPosition().getY() + ThePlayer::Instance()->getHeight() &&
					m_position.getY() < ThePlayer::Instance()->getPosition().getY() + ThePlayer::Instance()->getHeight()
					)))
			*/
		{
			//тут надо добавить уворот вверх или вниз
			
			//определяем в какую сторону ближе
			if (std::abs(playerCenter - bossTopY) > std::abs(playerCenter - bossBotY))
			{
				//вверх
				m_velocity.setY(-m_moveSpeed);
			}
			else
			{
				//вниз
				m_velocity.setY(m_moveSpeed);
			}


			/*
			m_tickCounter++;
			if (m_tickCounter == m_maxTicks)
			{
				m_tickCounter = 0;
			}
			*/
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
