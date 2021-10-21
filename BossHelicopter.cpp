#include "BossHelicopter.h"
#include "Game.h"
#include "SoundManger.h"

BossHelicopter::BossHelicopter()
{
	m_health = 20;
	m_dyingTime = 50;
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
		m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
		ShooterObject::update();

		//если уровень закончен, то финальный бой
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
