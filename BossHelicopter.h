#ifndef BOSSHELICOPTER_H
#define BOSSHELICOPTER_H
#include "Enemy.h"
#include "GameObjectFactory.h"

class BossHelicopter : public Enemy
{
public:

	BossHelicopter();
	virtual ~BossHelicopter();
	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();
	virtual void collision();


private:

	bool m_bHitted;
	int m_hitTimer;

};

class BossHelicopterCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new BossHelicopter();
	}
};


#endif

