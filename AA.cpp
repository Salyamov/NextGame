#include "AA.h"
#include "Game.h"
#include "BulletHandler.h"
#include "SoundManger.h"
#include <cmath>

AA::AA() : Enemy()
{
	m_health = 1;
	m_bulletFiringSpeed = 70;
	m_bulletSpeed = 2;
	m_dyingTime = 25;
}

void AA::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void AA::update()
{
	if (!m_bDying)
	{
		Vector2D playerPos = ThePlayer::Instance()->getPosition();
		float x = playerPos.getX() - m_position.getX();
		float y = playerPos.getY() - m_position.getY();

		float delta = std::sqrt(x * x + y * y) * (1 / m_bulletSpeed);

		x /= delta;
		y /= delta;
		Vector2D heading(x, y);

		//коордианты места(смещение), откуда вылетает ракета
		int rocketPosX = 0;
		int rocketPosY = 0;


		//тут вычислить угол до игрока и в зависимости от угла поставить соответсвующий кадр

		std::cout << (atan(y / x) * 180) / 3.14 << "\n";
		//слева
		if (x < 0)
		{
			if (fabs(atan(y / x) * 180) / 3.14 < 45) // меньше 45
			{
				if (fabs(atan(y / x) * 180) / 3.14 < 20)  //меньше 20
				{
					m_currentFrame = 0;
					rocketPosX = m_position.getX();
					rocketPosY = m_position.getY() + m_height / 4;
				}
				else //больше 20
				{
					m_currentFrame = 1;
					rocketPosX = m_position.getX();
					rocketPosY = m_position.getY() + m_height / 8;
				}
			}
			else //больше 45
			{
				if (fabs(atan(y / x) * 180) / 3.14 < 60) //больше 60
				{
					m_currentFrame = 2;
					rocketPosX = m_position.getX() + m_width / 8;
					rocketPosY = m_position.getY() + m_height / 16;
				}
				else //меньше 60
				{
					m_currentFrame = 3;
					rocketPosX = m_position.getX() + m_width / 4;
					rocketPosY = m_position.getY();
				}
			}

		}
		//справа
		else
		{
			if (fabs(atan(y / x) * 180) / 3.14 < 45)
			{
				if (fabs(tan(fabs(y / x)) * 180) / 3.14 < 20)
				{
					m_currentFrame = 4;
					rocketPosX = m_position.getX() + m_width;
					rocketPosY = m_position.getY() + m_height / 4;
				}
				else
				{
					m_currentFrame = 5;
					rocketPosX = m_position.getX() + m_width;
					rocketPosY = m_position.getY() + m_height / 8;

				}
			}
			else
			{
				if (fabs(atan(fabs(y / x)) * 180) / 3.14 < 60)
				{
					m_currentFrame = 6;
					rocketPosX = m_position.getX() + m_width - m_width / 8;
					rocketPosY = m_position.getY() + m_height / 16;
				}
				else
				{
					m_currentFrame = 7;
					rocketPosX = m_position.getX() + m_width - m_width / 4;
					rocketPosY = m_position.getY();
				}
			}

		}

		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet(rocketPosX, rocketPosY, 16, 16, "bullet2", 1, heading);
			TheSoundManager::Instance()->playSound("enemyshoot", 0);
			m_bulletCounter = 0;
		}
		m_bulletCounter++;

		
	}
	else
	{
		doDyingAnimation();
	}
	

	scroll(TheGame::Instance()->getScrollSpeed());
	ShooterObject::update();

}

void AA::collision()
{
	m_health -= 1;

	if (m_health == 0)
	{
		TheSoundManager::Instance()->playSound("explode", 0);

		m_textureID = "largeexplosion";
		m_currentFrame = 0;
		m_numFrames = 9;
		m_width = 60;
		m_height = 60;

		m_position.setX(m_position.getX() + m_width / 2);
		m_position.setY(m_position.getY() + m_height / 2);

		m_bDying = true;

	}

	TheGame::Instance()->addToGameScore(200);
}
