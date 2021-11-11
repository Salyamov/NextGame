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
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void collision();

	virtual std::string type() { return "Player"; }

	static Player* Instance()
	{
		return s_pInstance;
	}

	void setInstance(Player* player)
	{
		s_pInstance = player;
	}

	void setBossIsDead(bool dead)
	{
		m_bBossIsDead = true;
	}

	bool getPlayerShot() { return m_bShot; }

private:
	static Player* s_pInstance;

	//возращает игрока в центр экрана и делает неу€звимым, 
	//так же сбрасывает настройки текстуры(которые были во врем€ анимации смерти)
	void ressurect(); 
	void handleInput();
	void handleAnimation();

	//player can be invulnerable for a time
	int m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
	int m_invulnerableBlinkTime;

	bool m_bBossIsDead;
	bool m_bShot;
	bool m_bBlink;

};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}

};

typedef Player ThePlayer;



















#endif
