#include"Game.h"

Game* g_game = NULL;

/*
SDL_Renderer* g_pRenderer = NULL;
SDL_Window* g_pWindow = NULL;
bool g_bRunning;

bool init(const char* title, int x, int y, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		g_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
		if (g_pWindow == NULL)
			return false;
		else
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if (g_pRenderer == NULL)
				return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

void render()
{
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);
}

void update()
{

}

void handleEvents()
{

}

void clean()
{
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}
*/

int main(int argc, char* args[])
{
	g_game = new Game();

	g_game->init("NextGame", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	//g_game->init("NextGame", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	g_game->render();

	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}

	g_game->clean();

	return 0;
}