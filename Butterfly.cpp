#include "Butterfly.h"
#include "Game.h"
#include "SoundManger.h"

Butterfly::Butterfly() : Enemy()
{
	m_dyingTime = 25;
	m_moveSpeed = 2;
}

void Butterfly::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void Butterfly::update()
{
	if (!m_bDying)
	{
		scroll(TheGame::Instance()->getScrollSpeed());
		//тут написать поведение самонаводящейся ракеты
		Vector2D playerPos = ThePlayer::Instance()->getPosition();
		float x = playerPos.getX() - m_position.getX();
		float y = playerPos.getY() - m_position.getY();

		float delta = std::sqrt(x * x + y * y) * (1 / float(m_moveSpeed));


		if (std::fabs(x) > 300)
		{
			x /= delta;
			y /= delta;
			m_velocity.setX(x);
		}
		else
		{
			x /= delta;
			y /= delta;
			m_velocity.setX(x);
			m_velocity.setY(y);
		}


	}
	else
	{
		m_velocity.setX(0);
		m_velocity.setY(0);

		

		GameObject::scroll(TheGame::Instance()->getScrollSpeed());
		m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % m_numFrames);
		if (m_dyingCounter == m_dyingTime)
		{
			m_bDead = true;
		}
		m_dyingCounter++;
	}

	

	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
	ShooterObject::update();
}

void Butterfly::collision()
{
	m_currentRow = 1;
	m_numFrames = 4;
	
	if (!m_bDying)
	{
		TheSoundManager::Instance()->playSound("enemyexplode", 0);
	}
	m_bDying = true;
	
	TheGame::Instance()->addToGameScore(200);
}
