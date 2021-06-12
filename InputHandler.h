#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Game.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

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

	bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	bool getMouseButtonState(int buttonNumber)
	{
		return m_mouseButtonStates[buttonNumber];
	}

	void update();
	void clean();

private:
	InputHandler() {}
	~InputHandler() {}

	bool m_bJoysticksInitialised;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector< std::pair<Vector2D*, Vector2D*> > m_joysticksValues; //направление движения каждого стика
	std::vector< std::vector<bool>  > m_buttonStates; //массив кнопок для каждого устройства
	std::vector<bool> m_mouseButtonStates;

	const int m_joystickDeadZone = 5000;
	static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;





















#endif
