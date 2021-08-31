#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : ShooterObject()
{

}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(pParams);
	m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100 / m_animSpeed) % m_numFrames); //numFrames
}


void AnimatedGraphic::draw()
{
	ShooterObject::draw();
}

void AnimatedGraphic::clean()
{
}

