#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
public:
	Game() {}
	~Game() {}

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() { return m_bRunning; }

private:
	bool m_bRunning;
	SDL_Renderer* m_pRenderer;
	SDL_Window* m_pWindow;

	int m_currentFrame;
	
	std::vector<GameObject*> m_gameObjects;

	GameObject* m_player;
	GameObject* m_enemy1;
	GameObject* m_enemy2;
	GameObject* m_enemy3;

	/*
	GameObject m_go;
	Player m_player;
	*/
};


#endif
