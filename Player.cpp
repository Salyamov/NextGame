#include "Player.h"
#include "InputHandler.h"
#include "Game.h"

Player::Player() : ShooterObject()
{

}

void Player::load(std::unique_ptr<LoaderParams>const& pParams)
{
	ShooterObject::load(pParams);
}


void Player::draw()
{
	ShooterObject::draw();
}



void Player::update()
{
	//reset velocity
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();
	
	ShooterObject::update();
	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames); //num frames
}

void Player::clean()
{
}

void Player::handleInput()
{
	
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 50;


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

	m_textureID = "player";

	m_currentFrame = 0;
	m_numFrames = 5;
	m_width = 101;
	m_height = 46;

	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::handleAnimation()
{
	if (m_invulnerable)
	{
		//если неу€звимость закончилась
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



}

