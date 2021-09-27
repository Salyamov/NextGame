#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H
#include "GameState.h"
#include <string>

class  LoadingState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_loadingID; }

private:

	static const std::string s_loadingID;
};



#endif 

