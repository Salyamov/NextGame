#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy() : ShooterObject(), m_health(0)
{

}

/*
void Enemy::draw()
{
	SDLGameObject::draw();

}



void Enemy::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);

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
	m_velocity.setY(2);
	m_velocity.setX(0.001);

}


void Enemy::handleInput()
{
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
}
*/

Enemy::~Enemy()
{

}
