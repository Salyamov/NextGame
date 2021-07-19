#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(int animSpeed);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

private:
	int m_animSpeed;
};




























#endif
