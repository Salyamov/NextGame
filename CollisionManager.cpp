#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "TileLayer.h"

void CollisionManager::checkPlayerEnemyBulletCollision(Player* pPlayer)
{
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = pPlayer->getPosition().getX();
	pRect1->y = pPlayer->getPosition().getY();
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for (int i = 0; i < TheBulletHandler::Instance()->getEnemyBullets().size(); i++)
	{
		EnemyBullet* pEnemyBullet = TheBulletHandler::Instance()->getEnemyBullets()[i];

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = pEnemyBullet->getPosition().getX();
		pRect2->y = pEnemyBullet->getPosition().getY();
		pRect2->w = pEnemyBullet->getWidth();
		pRect2->h = pEnemyBullet->getHeight();

		if (RectRect(pRect1, pRect2))
		{
			if (!pPlayer->dying() && !pEnemyBullet->dying())
			{
				pEnemyBullet->collision();
				pPlayer->collision();
			}
		}
		delete pRect2;
	}

	delete pRect1;
}

void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		GameObject* pObject = objects[i];

		for (int j = 0; j < TheBulletHandler::Instance()->getPlayerBullets().size(); j++)
		{
			if (pObject->type() != std::string("Enemy") || !pObject->updating())
			{
				continue;
			}

			SDL_Rect* pRect1 = new SDL_Rect();
			pRect1->x = pObject->getPosition().getX();
			pRect1->y = pObject->getPosition().getY();
			pRect1->w = pObject->getWidth();
			pRect1->h = pObject->getHeight();

			PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->getPlayerBullets()[j];

			SDL_Rect* pRect2 = new SDL_Rect();
			pRect2->x = pPlayerBullet->getPosition().getX();
			pRect2->y = pPlayerBullet->getPosition().getY();
			pRect2->w = pPlayerBullet->getWidth();
			pRect2->h = pPlayerBullet->getHeight();

			if (RectRect(pRect1, pRect2))
			{
				if (!pObject->dying() && !pPlayerBullet->dying())
				{
					pPlayerBullet->collision();
					pObject->collision();
				}
		
			}
			delete pRect1;
			delete pRect2;
		}
	}
}

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects)
{
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = pPlayer->getPosition().getX();
	pRect1->y = pPlayer->getPosition().getY();
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
		{
			continue;
		}

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = objects[i]->getPosition().getX();
		pRect2->y = objects[i]->getPosition().getY();
		pRect2->w = objects[i]->getWidth();
		pRect2->h = objects[i]->getHeight();

		if (RectRect(pRect1, pRect2))
		{
			pPlayer->collision();
		}
		delete pRect2;
	}
	delete pRect1;

}

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{

}
