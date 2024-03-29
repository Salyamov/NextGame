#include "Player.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "Game.h"
#include "SoundManger.h"

Player* Player::s_pInstance = NULL;

Player::Player() :
	ShooterObject(),
	m_invulnerable(false),
	m_invulnerableTime(150),
	m_invulnerableCounter(0),
	m_invulnerableBlinkTime(0),
	m_bBossIsDead(false),
	m_bBlink(true),
	m_fireMode(SINGLE),
	m_bTileCollision(false)
{

}

void Player::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(std::move(pParams));

	m_bulletFiringSpeed = 12;
	m_moveSpeed = 4;

	m_bulletCounter = m_bulletFiringSpeed;

	m_dyingTime = 25;
	m_bShot = false;

	m_bulletSpeed = 17;
}


void Player::draw()
{
	ShooterObject::draw();
}



void Player::update()
{
	if (TheGame::Instance()->getLevelComplete())
	{
		if (m_bBossIsDead == true)
		{
			//���� �������� �� ���� ������ � ���������� ����� �������
			if (m_position.getX() >= TheGame::Instance()->getGameWidth())
			{
				m_invulnerable = false;
				m_bBlink = true;
				TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
			}
			//�������� �� ������ ��� ����������	
			else
			{
				m_invulnerable = true;
				m_bBlink = false;

				m_velocity.setY(0);
				m_velocity.setX(3);
				ShooterObject::update();
				handleAnimation();
			}
		}
		else
		{
			//battle with boss

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
	//if (!m_invulnerable && !TheGame::Instance()->getLevelComplete())

	if (!m_invulnerable)
	{
		m_textureID = "largeexplosion";
		m_currentFrame = 0;
		m_numFrames = 9;
		m_width = 60;
		m_height = 60;
		if (!m_bDying)
		{
			TheSoundManager::Instance()->playSound("explode", 0);
		}
		m_bDying = true;
	}
	else if(m_bTileCollision)
	{
		//�� ���� ����� � ����, ����� ����� ��������
		std::cout << "go away!\n";
		m_position.setX(10);
		m_position.setY(200);
		m_bTileCollision = false;
	}
}

void Player::handleInput()
{
	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
	{
		m_velocity.setY(-m_moveSpeed);
	}
	else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && m_position.getY() < TheGame::Instance()->getGameHeight() - m_height)
	{
		m_velocity.setY(m_moveSpeed);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
	{
		m_velocity.setX(-m_moveSpeed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && m_position.getX() < TheGame::Instance()->getGameWidth() - m_width)
	{
		m_velocity.setX(m_moveSpeed);
	}

	/*
	//��������� ��� �����
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LSHIFT))
	{
		TheGame::Instance()->setScrollSpeed(20);
		m_invulnerable = true;
		m_invulnerableCounter = 0;
		m_bBlink = false;
	}
	else 
	{
		TheGame::Instance()->setScrollSpeed(1);
		//m_invulnerable = false;
		m_textureID = "helicopter";
		m_width = 101;
		m_height = 46;
		m_numFrames = 5;
		m_currentFrame = 0;
		m_bBlink = true;

	}
	*/
	
	

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		if (m_bulletCounter >= m_bulletFiringSpeed)
		{
			if (m_fireMode == SINGLE)
			{
				TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + m_height / 2, 11, 11, "bullet1", 1, Vector2D(m_bulletSpeed, 0));
			}
			else if(m_fireMode == TRIPLE)
			{
				TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + m_height / 2, 11, 11, "bullet1", 1, Vector2D(20, 0));
				TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + m_height / 2, 11, 11, "bullet1", 1, Vector2D(17, -6));
				TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + m_height / 2, 11, 11, "bullet1", 1, Vector2D(17, 6));
			}

			TheSoundManager::Instance()->playSound("shoot", 0);
			m_bulletCounter = 0;
			m_bShot = true;
		}
		m_bulletCounter++;
	}
	else
	{
		m_bulletCounter++;
		//m_bulletCounter = m_bulletFiringSpeed;
		m_bShot = false;
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
	m_bBlink = true;

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
		else if(m_bBlink == true)
		{
			m_invulnerableBlinkTime++;
			if (m_alpha == 255 && m_invulnerableBlinkTime == 5)
			{
				m_alpha = 0;
				m_invulnerableBlinkTime = 0;
			}
			else if(m_alpha == 0 && m_invulnerableBlinkTime == 5)
			{
				m_alpha = 255;
				m_invulnerableBlinkTime = 0;
			}
		}
		m_invulnerableCounter++;
	}

	//�������� �����������
	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);

}

