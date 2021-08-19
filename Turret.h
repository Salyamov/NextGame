#ifndef TURRET_H
#define TURRET_H
#include "Enemy.h"
#include "GameObjectFactory.h"

class Turret : public Enemy
{
public:
	Turret();
	virtual ~Turret();
	virtual void update();

private:

};

class TurretCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new Turret();
	}
};





















#endif