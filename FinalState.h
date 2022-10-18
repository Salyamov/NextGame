#ifndef FINALSTATE_H
#define FINALSTATE_H
#include "GameState.h"
#include "GameObject.h"

class FinalState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_finalID; }

private:

	static const std::string s_finalID;
	std::vector<GameObject*> m_gameObjects;
};

#endif 

