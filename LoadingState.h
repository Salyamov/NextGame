#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H
#include "GameState.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <SDL_ttf.h>

class  LoadingState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_loadingID; }


private:

	static void s_loadingToPlay();

	static const std::string s_loadingID;
	std::vector<GameObject*> m_gameObjects;

};



#endif 

