#include "Game.h"

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
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
			}
		}
	}
	else
	{
		return false;
	}
	m_bRunning = true;

	TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer);

	m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

	/*
	m_go = new GameObject();
	m_player = new Player();
	m_enemy = new Enemy();

	m_go->load(100, 100, 128, 82, "animate");
	m_player->load(300, 300, 128, 82, "animate");
	m_enemy->load(0, 0, 128, 82, "animate");

	m_gameObjects.push_back(m_go);
	m_gameObjects.push_back(m_player);
	m_gameObjects.push_back(m_enemy);
	*/

	/*
	m_player = new Player();
	m_enemy1 = new Enemy();
	m_enemy2 = new Enemy();
	m_enemy3 = new Enemy();

	m_gameObjects.push_back(m_player);
	m_gameObjects.push_back(m_enemy1);
	m_gameObjects.push_back(m_enemy2);
	m_gameObjects.push_back(m_enemy3);
	*/

	/*
	m_go.load(100, 100, 128, 82, "animate");
	m_player.load(300, 300, 128, 82, "animate");
	*/

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	/*
	m_go.draw(m_pRenderer);
	m_player.draw(m_pRenderer);
	*/
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;

		default:
			break;
		}
	}

}

void Game::update()
{
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
	/*
	m_go.update();
	m_player.update();
	*/

}