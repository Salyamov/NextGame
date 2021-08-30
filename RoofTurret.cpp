#include "RoofTurret.h"
#include "TextureManager.h"
#include "Game.h"
#include "BulletHandler.h"

RoofTurret::~RoofTurret()
{
}

void RoofTurret::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width,
		m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_VERTICAL);
}

void RoofTurret::update()
{
	if (!m_bDying)
	{
		scroll(TheGame::Instance()->getScrollSpeed());

		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheBulletHandler::Instance()->addEnemyBullet();
			TheBulletHandler::Instance()->addEnemyBullet();
			TheBulletHandler::Instance()->addEnemyBullet();
			m_bulletCounter = 0;
		}
		m_bulletCounter++;
	}
	else
	{
		scroll(TheGame::Instance()->getScrollSpeed());
		doDyingAnimation();
	}
}
