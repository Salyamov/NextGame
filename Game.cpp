#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "Player.h"
#include "Enemy.h"



Game* Game::s_pInstance = NULL;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow == NULL)
			return false;
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer == NULL)
				return false;
			else
			{
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
		}
	}
	else
	{
		return false;
	}
	
	/*
	TheInputHandler::Instance()->initializeJoysticks();
	*/

	m_width = width;
	m_height = height;
	
	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	m_bRunning = true;

	return true;
}

void Game::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TheInputHandler::Instance()->clean();
	SDL_Quit();
}

void Game::quit()
{
	m_bRunning = false;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
	
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}