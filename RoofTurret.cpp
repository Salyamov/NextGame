#include "RoofTurret.h"
#include "TextureManager.h"
#include "Game.h"
#include "BulletHandler.h"

RoofTurret::~RoofTurret()
{
}

void RoofTurret::draw()
{
	if (m_alpha < 255)
	{
		TextureManager::Instance()->drawFrame(m_textureID2, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width,
			m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), m_angle, 255, SDL_FLIP_VERTICAL);
	}
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
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-3, 3));
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(0, 3));
			TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(3, 3));
			m_bulletCounter = 0;
		}
		m_bulletCounter++;
	}
	else
	{
		//scroll(TheGame::Instance()->getScrollSpeed());
		doDyingAnimation();
	}
}
