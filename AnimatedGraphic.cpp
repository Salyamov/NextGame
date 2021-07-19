#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : m_animSpeed(0)
{

}

void AnimatedGraphic::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100 / m_animSpeed) % 2);
}


void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::clean()
{
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}
