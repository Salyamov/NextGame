#include "BossAA.h"
#include "Game.h"

BossAA::BossAA()
{
}

void BossAA::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void BossAA::update()
{
	if (!TheGame::Instance()->getLevelComplete())
	{
		scroll(TheGame::Instance()->getScrollSpeed());
	}

	//m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
	//ShooterObject::update();


}

void BossAA::collision()
{
}
