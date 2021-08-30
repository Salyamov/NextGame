#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include <iostream>
#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{
public:

	void checkPlayerEnemyBulletCollision(Player* pPlayer);
	void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
	void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects);
	void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

private:

};



























#endif
