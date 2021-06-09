#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Game.h"



class InputHandler
{
public:

	static InputHandler* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new InputHandler();
			return s_pInstance;
		}
		return s_pInstance;
	}

	void initializeJoysticks();
	bool joystickInitialized()
	{
		return m_bJoysticksInitialised;
	}

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	void update();
	void clean();
private:
	InputHandler() {}
	~InputHandler() {}

	bool m_bJoysticksInitialised;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector< std::pair<Vector2D*, Vector2D*> > m_joysticksValues; //направление движения каждого стика

	const int m_joystickDeadZone = 5000;
	static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;





















#endif
