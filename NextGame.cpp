#include"Game.h"

Game* g_game = NULL;

int main(int argc, char* args[])
{
	g_game = new Game();

	g_game->init("NextGame", 100, 100, 640, 480, false);
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