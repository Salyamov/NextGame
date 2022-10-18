#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H
#include "Layer.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include <vector>

class ObjectLayer : public Layer
{
public:

	virtual void update(Level* pLevel);
	virtual void render();
	
	virtual ~ObjectLayer();

	std::vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}

private:
	std::vector<GameObject*> m_gameObjects;
	CollisionManager m_collisionManager;
};






















#endif
