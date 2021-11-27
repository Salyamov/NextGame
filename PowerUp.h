#ifndef POWERUP_H
#define POWERUP_H
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class PowerUp : public ShooterObject
{
public:
	PowerUp() {}
	~PowerUp() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();
	virtual void collision();

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

