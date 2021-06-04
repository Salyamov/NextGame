#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams)
{
	m_x = pParams->getX();
	m_y = pParams->getY();
	m_height = pParams->getHeight();
	m_width = pParams->getWidth();
	m_textureID = pParams->getTextureID();
	m_currentFrame = 1;
	m_currentRow = 1;
}

void SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width,
		m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
}

void SDLGameObject::update()
{
}

void SDLGameObject::clean()
{
}
