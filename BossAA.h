#ifndef BOSSAA_H
#define BOSSAA_H
#include "Enemy.h"
#include "GameObjectFactory.h"

class BossAA : public Enemy
{
public:
	BossAA();
	virtual ~BossAA() { }

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();
	virtual void collision();


private:

	float m_bulletSpeed;

	bool m_bHitted;
	int m_hitTimer;


};

class BossAACreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new BossAA();
	}
};











#endif
