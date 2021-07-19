#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton();
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
	void (*m_callback)(); //function pointer
	bool m_bReleased;
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};
























#endif 
