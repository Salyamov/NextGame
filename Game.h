#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"



class Game
{
public:

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();

	bool running() { return m_bRunning; }

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	static Game* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

private:
	Game() {}
	static Game* s_pInstance;
	

	bool m_bRunning;
	SDL_Renderer* m_pRenderer;
	SDL_Window* m_pWindow;

	int m_currentFrame;

	std::vector<GameObject*> m_gameObjects;
	GameObject* m_go;
	GameObject* m_player;
	GameObject* m_enemy;

};

typedef Game TheGame;
#endif
