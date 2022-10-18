#ifndef ENEMY_H
#define ENEMY_H
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{
public:
	virtual std::string type() { return "Enemy"; }

protected:
	int m_health;
	int m_maxHealth;

	Enemy();
	virtual ~Enemy();
};






















#endif
