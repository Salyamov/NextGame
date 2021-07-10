#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "PauseState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/helicopter.png", "helicopter", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/helicopter2.png", "helicopter2", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(new LoaderParams(500, 100, 128, 55, "helicopter"));
	GameObject* enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2"));

	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy);

	std::cout << "Entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("helicopter");

	std::cout << "Exiting PlayState\n";
	return true;
}
