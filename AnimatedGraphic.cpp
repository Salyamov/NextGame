#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams), m_animSpeed(animSpeed)
{

}

void AnimatedGraphic::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100 / m_animSpeed) % 5);
}


void AnimatedGraphic::draw()
{
}

void AnimatedGraphic::clean()
{
}