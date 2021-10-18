#ifndef SHOOTEROBJECT_H
#define SHOOTEROBJECT_H
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject() {} //for polymorphism
	virtual void load(std::unique_ptr<LoaderParams>const& pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented in this class
	virtual std::string type() { return "ShooterObject"; }

protected:

	ShooterObject(); // we won't directly create Shooter object

	void doDyingAnimation();//обновляет анимацию и ставит флаг dead, чтобы можно было удалить объект из игры

	void changeColor(Uint8 r, Uint8 g, Uint8 b);//color modulation

	int m_bulletFiringSpeed;
	int m_bulletCounter;
	int m_moveSpeed;

	//animation time
	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound; //has the explosion sound played?

};






















#endif
