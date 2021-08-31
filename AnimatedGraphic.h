#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
public:
	AnimatedGraphic();
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(std::unique_ptr<LoaderParams> const& pParams);

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
