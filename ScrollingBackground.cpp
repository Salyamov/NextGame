#include "ScrollingBackground.h"
#include "Game.h"
#include "TextureManager.h"

ScrollingBackground::ScrollingBackground() : ShooterObject()
{
	m_count = 0;
	m_maxcount = 1;
}

ScrollingBackground::~ScrollingBackground()
{
}

void ScrollingBackground::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(std::move(pParams));
	m_maxcount = pParams->getAnimSpeed();

	m_scrollSpeed = 1;

	//first rectangle properties
	m_srcRect1.x = 0;
	m_destRect1.x = m_position.getX();
	m_srcRect1.y = 0;
	m_destRect1.y = m_position.getY();

	m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_dstRect1Width = m_width;
	m_srcRect1.h = m_destRect1.h = m_height;

	//second rectangle properties
	m_srcRect2.x = 0;
	m_srcRect2.y = 0;
	m_destRect2.x = m_position.getX() + m_width;
	m_destRect2.y = m_position.getY();

	m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_dstRect2Width = 0;
	m_srcRect2.h = m_destRect2.h = m_height;

}

void ScrollingBackground::draw()
{
	//draw first rectangle

	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),
		TheTextureManager::Instance()->getTextureMap()[m_textureID], &m_srcRect1, &m_destRect1, 0, 0, SDL_FLIP_NONE);

	//draw second rectangle

	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),
		TheTextureManager::Instance()->getTextureMap()[m_textureID], &m_srcRect2, &m_destRect2, 0, 0, SDL_FLIP_NONE);

}

void ScrollingBackground::update()
{
	if (m_count >= m_maxcount)
	{
		//make first rectangle smaller(src1 dst1)
		m_srcRect1.x += m_scrollSpeed;
		m_srcRect1.w -= m_scrollSpeed;
		m_destRect1.w -= m_scrollSpeed;

		//make second rectangle bigger(src2 dst2)
		m_srcRect2.w += m_scrollSpeed;
		m_destRect2.x -= m_scrollSpeed;
		m_destRect2.w += m_scrollSpeed;


		//reset and start again
		if (m_destRect2.w >= m_width)
		{
			m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_dstRect1Width = m_width; // who is m_srcRect2Width and m_dstRect1Width ? 
			m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_dstRect2Width = 0; // m_srcRect2Width, m_dstRect2Width ?
			m_srcRect1.h = m_destRect1.h = m_height;
			m_srcRect2.h = m_destRect2.h = m_height;

			//src1.x dst1.x
			m_srcRect1.x = 0;
			m_srcRect1.y = 0;
			m_destRect1.x = m_position.getX();
			m_destRect1.y = m_position.getY();

			//src2.x dst2.x
			m_srcRect2.x = 0;
			m_srcRect2.y = 0;
			m_destRect2.x = m_position.getX() + m_width;
			m_destRect2.y = m_position.getY();

		}
		m_count = 0;
	}

	m_count++;

}

void ScrollingBackground::clean()
{
}
