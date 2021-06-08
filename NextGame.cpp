#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <Windows.h>
#include <iostream>

const int FPS = 60;
const int DELAY_TIME = 1000.f / FPS;

Game* g_game = NULL;

int main(int argc, char* args[])
{
	AllocConsole();
	FILE* file;
	file = freopen("CON", "w", stdout);

	Uint32 frameStart, frameTime;

	if (TheGame::Instance()->init("NextGame", 100, 100, 640, 480, false))
	{
		std::cout << "game init complete\n";
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart; //сколько понадобилось времени на одну прорисовку

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)DELAY_TIME - frameTime);
			}
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