#ifndef BOSSDRAGON_H
#define BOSSDRAGON_H
#include "Enemy.h"
#include "GameObjectFactory.h"


class BossDragon : public Enemy
{
public:
	BossDragon();
	virtual ~BossDragon() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();
	virtual void collision();

private:


};

class BossDragonCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new BossDragon();
	}
};

#endif // ! BOSSDRAGON_H

