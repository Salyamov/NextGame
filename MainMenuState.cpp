#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include "InputHandler.h"
#include "LoadingState.h"
#include <iostream>

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
		//std::cout << "drawing object " << m_gameObjects[i]->type() << "\n";
	}
}

bool MainMenuState::onEnter()
{
	StateParser stateParser;

	stateParser.parseState("assets/test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "Entering MenuState\n";
	return true;
}

bool MainMenuState::onExit()
{
	m_exiting = true;

	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->clean();
			m_gameObjects.pop_back();
		}
	}
	m_gameObjects.clear();
	
	/*
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	*/

	TheInputHandler::Instance()->reset();

	std::cout << "Exiting MenuState\n";
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//if MenuButton type
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new LoadingState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}
