#ifndef SPEEDUP_H
#define SPEEDUP_H
#include "PowerUp.h"


class SpeedUp : public PowerUp
{
public:
	SpeedUp();
	virtual ~SpeedUp() { }
	virtual void collision();

private:

};

class SpeedUpCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new SpeedUp();
	}
};





















#endif