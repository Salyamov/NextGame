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
#include "Glider.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Turret.h"
#include "RoofTurret.h"
#include "GameOverState.h"
#include "ScrollingBackground.h"


Game* Game::s_pInstance = NULL;

Game::Game() : m_pWindow(0), 
			   m_pRenderer(0),
			   m_bRunning(false),
			   m_pGameStateMachine(0),
			   m_playerLives(3),
			   m_bLevelComplete(false),
			   m_bChangingState(false),		   		   
			   m_scrollSpeed(0.8),
			   m_width(0),
			   m_height(0)
{
	m_levelFiles.push_back("assets/map1.tmx");

	m_currentLevel = 1;
}

Game::~Game()
{
	m_pRenderer = 0;
	m_pWindow = 0;
}

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
	TheGameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
	TheGameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
	TheGameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
	TheGameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
	TheGameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
	TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
	

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	m_bRunning = true;

	return true;
}

void Game::clean()
{
	TheInputHandler::Instance()->clean();



	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::quit()
{
	m_bRunning = false;
}

void Game::setCurrentLevel(int currentLevel)
{
	m_currentLevel = currentLevel;
	m_pGameStateMachine->changeState(new GameOverState()); //тут можно поставить состояние между уровнями
	m_bLevelComplete = false;
}

int Game::getCurrentLevel()
{
	return m_currentLevel;
}

float Game::getScrollSpeed()
{
	return m_scrollSpeed;
}

void Game::setPlayerLives(int playerLives)
{
	m_playerLives = playerLives;
}

int Game::getPlayerLives()
{
	return m_playerLives;
}

void Game::setLevelComplete(bool levelComplete)
{
	m_bLevelComplete = levelComplete;
}

bool Game::getLevelComplete()
{
	return m_bLevelComplete;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
	
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