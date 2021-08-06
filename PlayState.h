#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Level.h"
//#include "SDLGameObject.h"
//#include "GameObject.h"
#include <string>
#include <vector>

class GameObject;
class SDLGameObject;

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID;  }

private:

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
	Level* pLevel;
};


























#endif