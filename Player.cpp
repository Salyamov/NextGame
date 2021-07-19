#include "Player.h"
#include "InputHandler.h"

Player::Player() : SDLGameObject()
{

}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}


void Player::draw()
{
	SDLGameObject::draw();
}



void Player::update()
{
	//reset velocity
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();
	
	SDLGameObject::update();
	m_currentFrame = int((SDL_GetTicks() / 100) % 5); //num frames
}

void Player::clean()
{
}

void Player::handleInput()
{
	
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 50;

	
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
		/*
		if (TheInputHandler::Instance()->xvalue(0, 2) > 0 || TheInputHandler::Instance()->xvalue(0, 2) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
		}
		if (TheInputHandler::Instance()->yvalue(0, 2) > 0 || TheInputHandler::Instance()->yvalue(0, 2) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
		}
		*/
	



	}


}

