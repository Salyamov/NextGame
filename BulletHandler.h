#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H
#include <vector>
#include "Bullet.h"
#include "Vector2D.h"


class BulletHandler
{
public:

	void addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
	void addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

	void updateBullets();
	void drawBullets();
	
	void clearBullets();
	void deleteBullet(PlayerBullet* bullet);

	const std::vector<PlayerBullet*> getPlayerBullets() { return m_playerBullets; }
	const std::vector<EnemyBullet*>  getEnemyBullets() { return m_enemyBullets; }

	static BulletHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new BulletHandler;
			return s_pInstance;
		}
		return s_pInstance;
	}

private:
	
	static BulletHandler* s_pInstance;
	BulletHandler();
	~BulletHandler();

	std::vector<PlayerBullet*> m_playerBullets;
	std::vector<EnemyBullet*> m_enemyBullets;


};

typedef BulletHandler TheBulletHandler;























#endif
