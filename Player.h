#ifndef PLAYER_H
#define PLAYER_H
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:
	Player();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(std::unique_ptr<LoaderParams>const& pParams);

private:
	//возращает игрока в центр экрана и делает неу€звимым, 
	//так же сбрасывает настройки текстуры(которые были во врем€ анимации смерти)
	void ressurect(); 
	void handleInput();
	void handleAnimation();

	//player can be invulnerable for a time
	int m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;

};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}

};





















#endif
