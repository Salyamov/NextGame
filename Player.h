#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "SDLGameObject.h"


class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:

};





















#endif
