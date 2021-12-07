#include "BossDragon.h"
#include "Game.h"

BossDragon::BossDragon()
{

}

void BossDragon::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void BossDragon::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
	ShooterObject::update();

	//если уровень не закончен, то скроллим
	if (!TheGame::Instance()->getLevelComplete())
	{
		scroll(TheGame::Instance()->getScrollSpeed());
	}
}

void BossDragon::collision()
{
}
