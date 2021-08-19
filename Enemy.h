#ifndef ENEMY_H
#define ENEMY_H
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{
/*
public:
	
	Enemy();

	virtual void draw(); // -> child
	virtual void update(); // -> child
	virtual void clean(); // -> child
	virtual void load(const LoaderParams* pParams); // -> child

private:
	void handleInput();
	*/

public:
	virtual std::string type() { return "Enemy"; }

protected:
	int m_health;

	Enemy();
	virtual ~Enemy();
};


/*
class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};
*/





















#endif
