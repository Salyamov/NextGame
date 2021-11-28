#ifndef POWERUP_H
#define POWERUP_H
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class PowerUp : public ShooterObject
{
public:
	PowerUp();
	virtual ~PowerUp() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();
	virtual void draw();
	virtual void collision();
	virtual std::string type() { return "PowerUp"; }

private:


};

class PowerUpCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new PowerUp();
	}
};

#endif // !POWERUP_H

