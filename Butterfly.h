#ifndef BUTTERFLY_H
#define BUTTERFLY_H
#include "Enemy.h"
#include "GameObjectFactory.h"

class Butterfly : public Enemy
{
public:
	Butterfly();
	virtual ~Butterfly() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();
	virtual void collision();

private:


};

class ButterflyCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new Butterfly();
	}
};

#endif 

