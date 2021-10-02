#include "LoadingState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "Game.h"
#include "InputHandler.h"

const std::string LoadingState::s_loadingID = "LOADING";

void LoadingState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	}
}

void LoadingState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool LoadingState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_loadingID, &m_gameObjects, &m_textureIDList);

	//TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
	std::cout << "Entering LoadingState\n";

	return true;
}

bool LoadingState::onExit()
{


	std::cout << "Exiting LoadingState\n";

	return true;
}

void LoadingState::s_loadingToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
