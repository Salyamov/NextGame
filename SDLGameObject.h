#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
//#include "Game.h"
//#include "TextureManager.h"


class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
protected:

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;

	std::string m_textureID;

};






















#endif
