#ifndef ESKELETOR_H
#define ESKELETOR_H
#include "Enemy.h"
#include "GameObjectFactory.h"

class Eskeletor : public Enemy
{
public:
	Eskeletor();
	virtual ~Eskeletor();
	virtual void update();

private:

};

class EskeletorCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new Eskeletor();
	}
};
























#endif
