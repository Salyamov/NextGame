#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy() : SDLGameObject()
{

}

void Enemy::draw()
{
	SDLGameObject::draw();
	m_velocity.setY(2);
	m_velocity.setX(0.001);
}



void Enemy::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100) % 5);

	if (m_position.getY() < 0)
	{
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 400)
	{
		m_velocity.setY(-2);
	}

	SDLGameObject::update();
}

void Enemy::clean()
{
}

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);

}

void Enemy::handleInput()
{
	if (TheInputHandler::Instance()->joystickInitialized())
	{
		//1 stick
		/*
		if (TheInputHandler::Instance()->xvalue(0, 1) > 0 || TheInputHandler::Instance()->xvalue(0, 1) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
		}
		if (TheInputHandler::Instance()->yvalue(0, 1) > 0 || TheInputHandler::Instance()->yvalue(0, 1) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
		}
		*/

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
