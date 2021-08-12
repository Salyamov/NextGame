#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include "GameStateMachine.h"

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
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	int getGameWidth() const { return m_width; }
	int getGameHeight() const { return m_height; }

	void setCurrentLevel(int currentLevel);
	int getCurrentLevel();
	float getScrollSpeed();
	void setPlayerLives(int playerLives);
	int getPlayerLives();
	void setLevelComplete(bool levelComplete);
	bool getLevelComplete();


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
	GameStateMachine* m_pGameStateMachine;

	int m_width;
	int m_height;

	int m_currentLevel;
	float m_scrollSpeed;
	int m_playerLives;
	bool m_bLevelComplete;
};

typedef Game TheGame;
#endif
