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

	Vector2D* getMousePosition()
	{
		return m_mousePosition;
	}

	bool isKeyDown(SDL_Scancode key)
	{
		if (m_keyStates != 0)
		{
			if (m_keyStates[key] == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	void update();
	void clean();

private:
	InputHandler();
	~InputHandler() {}

	bool m_bJoysticksInitialised;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector< std::pair<Vector2D*, Vector2D*> > m_joysticksValues; //направление движения каждого стика
	std::vector< std::vector<bool>  > m_buttonStates; //массив кнопок для каждого устройства
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
	const Uint8* m_keyStates;

	//handle keyboard events
	void onKeyDown();
	void onKeyUp();

	//handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	//handle joystick events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	const int m_joystickDeadZone = 5000;
	static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;





















#endif
