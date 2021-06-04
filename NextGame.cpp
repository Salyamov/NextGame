#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <Windows.h>
#include <iostream>


Game* g_game = NULL;

int main(int argc, char* args[])
{

	AllocConsole();
	FILE* file;
	file = freopen("CON", "w", stdout);

	if (TheGame::Instance()->init("NextGame", 100, 100, 640, 480, false))
	{
		std::cout << "game init complete\n";
		while (TheGame::Instance()->running())
		{
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			SDL_Delay(20);
		}
	}
	else
	{
		std::cout << "game init failed\n" << SDL_GetError() << "\n";
		return -1;
	}
	std::cout << "game closing\n";
	TheGame::Instance()->clean();

	return 0;
}