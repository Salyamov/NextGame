#ifndef SCROLLINGBACKGROUND_H
#define SCROLLINGBACKGROUND_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class ScrollingBackground : public ShooterObject
{
public:
	ScrollingBackground();
	virtual ~ScrollingBackground();

	virtual void load(std::unique_ptr<LoaderParams>const& pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:

	int m_scrollSpeed;

	int count;
	int maxcount;

	SDL_Rect m_srcRect1;
	SDL_Rect m_srcRect2;

	SDL_Rect m_destRect1;
	SDL_Rect m_destRect2;

	int m_srcRect1Width;
	int m_srcRect2Width;

	int m_dstRect1Width;
	int m_dstRect2Width;

};

class ScrollingBackgroundCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new ScrollingBackground();
	}
};























#endif
