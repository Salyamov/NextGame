#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H
#include "GameState.h"
//#include "PlayState.h"
//#include "MenuState.h"
#include <vector>

class GameStateMachine
{
public:
	void pushState(GameState* pState); //��������� ����� ���������
	void changeState(GameState* pState); //������� ������ � ��������� ����� ���������
	void popState(); //������� ������ ���������
	void render();
	void update();
private:
	std::vector<GameState*> m_gameStates;
};


























#endif