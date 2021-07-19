#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic();
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

private:
	int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}
};






























#endif
