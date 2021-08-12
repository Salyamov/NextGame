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
	virtual std::string type() { return "SDLGameObject"; }

	/*
	virtual void load(const LoaderParams* pParams);
	Vector2D& getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	*/

protected:

	ShooterObject(); // we won't directly create Shooter object

	//draw the animation
	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	//animation time
	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound; //explosion sound played?

	/*
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;
	int m_numFrames;

	std::string m_textureID;
	*/
};






















#endif
