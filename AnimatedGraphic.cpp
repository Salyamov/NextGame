#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{

}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100 / m_animSpeed) % m_numFrames); //numFrames
}


void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::clean()
{
}

