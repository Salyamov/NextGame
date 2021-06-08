#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

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

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;

	std::string m_textureID;

};






















#endif
