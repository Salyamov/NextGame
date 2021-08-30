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
	virtual void collision();

private:

	int m_maxHeight;
	int m_minHeight;
	int m_gap;

};

class GliderCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new Glider();
	}
};























#endif