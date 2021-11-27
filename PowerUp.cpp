#include "PowerUp.h"
#include "Player.h"
#include "Game.h"

PowerUp::PowerUp(): ShooterObject()
{
	/*
	m_currentFrame = 0;
	m_numFrames = 3;
	m_width = 37;
	m_height = 34;
	*/
}

void PowerUp::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void PowerUp::update()
{
	scroll(TheGame::Instance()->getScrollSpeed());

	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);

}

void PowerUp::draw()
{
	ShooterObject::draw();

}

void PowerUp::collision()
{
	//тут происходит апргрейд игрока и исчезает сам объект
	std::cout << "PowerUp \n";
	ThePlayer::Instance()->setFireMode(TRIPLE);
	m_bDead = true;
}
