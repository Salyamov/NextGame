#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include <vector>

class MenuState : public GameState
{
protected:
	//typedef void(*Callback)(); //указатель на функцию становится типом
	using Callback = void(*)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
	
	std::vector<Callback> m_callbacks;

};



























#endif
