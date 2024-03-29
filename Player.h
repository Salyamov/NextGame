#ifndef PLAYER_H
#define PLAYER_H
#include "ShooterObject.h"
#include "GameObjectFactory.h"

enum FireMode
{
	SINGLE,
	TRIPLE
};

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

	void setFireMode(FireMode mode)
	{
		m_fireMode = mode;
	}

	bool getPlayerShot() { return m_bShot; }
	
	void increaseMoveSpeed() { m_moveSpeed++; }

	void setTileCollision(bool collision) { m_bTileCollision = true; }
	bool getInvulnerableState() { return m_invulnerable; }

private:
	static Player* s_pInstance;

	//��������� ������ � ����� ������ � ������ ����������, 
	//��� �� ���������� ��������� ��������(������� ���� �� ����� �������� ������)
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

	int m_fireMode;
	int m_bulletSpeed;

	bool m_bTileCollision;

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
