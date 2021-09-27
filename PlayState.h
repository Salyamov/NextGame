#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Level.h"
#include "CollisionManager.h"
#include <string>
#include <vector>

class GameObject;
class ShooterObject;

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID;  }

private:

	static const std::string s_playID;
	Level* pLevel;
	CollisionManager m_collisionManager;
};


























#endif