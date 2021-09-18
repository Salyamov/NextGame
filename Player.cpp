#include "Player.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "Game.h"

Player::Player() : ShooterObject(), m_invulnerable(false), m_invulnerableTime(200), m_invulnerableCounter(0)
{

}

void Player::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(std::move(pParams));

	m_bulletFiringSpeed = 13;
	m_moveSpeed = 3;

	m_bulletCounter = m_bulletFiringSpeed;

	m_dyingTime = 100;

}


void Player::draw()
{
	ShooterObject::draw();
}



void Player::update()
{
	if (TheGame::Instance()->getLevelComplete())
	{
		//�������� �� ���� ������ � ���������� ����� �������
		if (m_position.getX() >= TheGame::Instance()->getGameWidth())
		{
			TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
		}
		//�������� �� ������ ��� ����������
		else
		{
			m_velocity.setY(0);
			m_velocity.setX(3);
			ShooterObject::update();
			handleAnimation();
		}
	}
	else
	{
		if (!m_bDying)
		{
			//reset velocity
			m_velocity.setX(0);
			m_velocity.setY(0);

			//get input
			handleInput();
			ShooterObject::update();
			handleAnimation();

		}
		//if player doing the death animation
		else
		{
			m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
			//if death animation is completed
			if (m_dyingCounter == m_dyingTime)
			{
				//ressurect the player
				ressurect();
			}
			m_dyingCounter++;
		}
	}

}

void Player::clean()
{
}

void Player::collision()
{
	if (!m_invulnerable && !TheGame::Instance()->getLevelComplete())
	{
		m_textureID = "largeexplosion";
		m_currentFrame = 0;
		m_numFrames = 9;
		m_width = 60;
		m_height = 60;
		m_bDying = true;
	}
}

void Player::handleInput()
{
	
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 50;

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10, 0));
			m_bulletCounter = 0;
		}
		m_bulletCounter++;
	}
	else
	{
		m_bulletCounter = m_bulletFiringSpeed;
	}


	/*
	if (TheInputHandler::Instance()->joystickInitialized())
	{
		//1 stick		
		if (TheInputHandler::Instance()->xvalue(0, 1) > 0 || TheInputHandler::Instance()->xvalue(0, 1) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
		}
		if (TheInputHandler::Instance()->yvalue(0, 1) > 0 || TheInputHandler::Instance()->yvalue(0, 1) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
		}
				
		//2 stick	
		if (TheInputHandler::Instance()->xvalue(0, 2) > 0 || TheInputHandler::Instance()->xvalue(0, 2) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
		}
		if (TheInputHandler::Instance()->yvalue(0, 2) > 0 || TheInputHandler::Instance()->yvalue(0, 2) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
		}
	}
	*/

}

void Player::ressurect()
{
	TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);

	m_position.setX(10);
	m_position.setY(200);
	m_bDying = false;

	m_textureID = "helicopter";

	m_currentFrame = 0;
	m_numFrames = 5;
	m_width = 101;
	m_height = 46;

	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::handleAnimation()
{
	//���� �������� ����������, �� �� ������
	if (m_invulnerable)
	{
		//���� ������������ �����������
		if (m_invulnerableCounter == m_invulnerableTime)
		{
			m_invulnerable = false;
			m_invulnerableCounter = 0;
			m_alpha = 255;
		}
		else
		{
			if (m_alpha == 255)
			{
				m_alpha = 0;
			}
			else
			{
				m_alpha = 255;
			}
		}
		m_invulnerableCounter++;
	}

	//������ ��������� �� ����� ��������
	if (!m_bDead)
	{
		if (m_velocity.getX() < 0)
		{
			m_angle = -10.0;
		}
		else if (m_velocity.getX() > 0)
		{
			m_angle = 10.0;
		}
		else
		{
			m_angle = 0.0;
		}
	}

	//�������� �����������
	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);

}

