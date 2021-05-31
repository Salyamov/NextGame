#define _CRT_SECURE_NO_WARNINGS
#include"Game.h"
#include<Windows.h>
#include<iostream>


Game* g_game = NULL;

int main(int argc, char* args[])
{

	AllocConsole();
	FILE* file;
	file = freopen("CON", "w", stdout);

	g_game = new Game();

	g_game->init("NextGame", 100, 100, 640, 480, false);

	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}

	g_game->clean();

	return 0;
}