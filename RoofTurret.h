#ifndef ROOFTURRET_H
#define ROOFTURRET_H
#include "Turret.h"
#include "GameObjectFactory.h"

class RoofTurret : public Turret
{
public:
	virtual ~RoofTurret();
	virtual void draw();
	virtual void update();

private:

};


class RoofTurretCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new RoofTurret();
	}
};




















#endif