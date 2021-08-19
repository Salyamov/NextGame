#ifndef GLIDER_H
#define GLIDER_H
#include "Enemy.h"
#include "GameObjectFactory.h"

class Glider : public Enemy
{
public:
	Glider();
	virtual ~Glider();

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();

private:

	int m_maxHeight;
	int m_minHeight;
	int m_gap;

	int m_dyingTime;
	int m_health;
	int m_moveSpeed;

};

class GliderCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new Glider();
	}
};























#endif