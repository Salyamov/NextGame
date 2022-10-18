#include "Bullet.h"
#include "BulletHandler.h"

void PlayerBullet::collision()
{
	TheBulletHandler::Instance()->deleteBullet(this);
}
