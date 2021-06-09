#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}

void Enemy::draw()
{
	SDLGameObject::draw();
}



void Enemy::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();

	SDLGameObject::update();
	m_currentFrame = int((SDL_GetTicks() / 100) % 6);
}

void Enemy::clean()
{
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
