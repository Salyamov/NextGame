#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>
#include <vector>

class GameState {
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:

	std::vector<std::string> m_textureIDList;
	
	bool m_loadingComplete;
	bool m_exiting;

	GameState() : m_loadingComplete(false), m_exiting(false) { }

};


























#endif
