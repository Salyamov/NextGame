#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H
#include "GameState.h"
//#include "PlayState.h"
//#include "MenuState.h"
#include <vector>

class GameStateMachine
{
public:
	void pushState(GameState* pState); //добавляет новое состояние
	void changeState(GameState* pState); //удаляет старое и добавляет новое состояние
	void popState(); //удаляет старое состояние
	void render();
	void update();
private:
	std::vector<GameState*> m_gameStates;
};


























#endif