#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "GameState.h"
#include "MenuState.h"
#include <vector>

class GameObject;

class GameOverState : public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static void s_gameOverToMain();
	static void s_restartPlay();

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static const std::string s_gameOverID;

	std::vector<GameObject*> m_gameObjects;
};

























#endif
