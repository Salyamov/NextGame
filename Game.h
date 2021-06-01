#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<SDL_image.h>

#include"TextureManager.h"
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
	//TextureManager m_TextureManager;

};


#endif
