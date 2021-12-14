#include <iostream>
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "BulletHandler.h"
#include "TextManager.h"
#include "SoundManger.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	//��� �������� �� ���� �������� �������� � ���� ������ (m_loadingComplete � m_exiting)
	if (m_loadingComplete && !m_exiting)
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheGame::Instance()->getStateMachine()->pushState(new PauseState());
		}

		TheBulletHandler::Instance()->updateBullets();

		if (TheGame::Instance()->getPlayerLives() == 0)
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}

		if (pLevel != 0)
		{
			pLevel->update();
		}

		std::string msg;
		msg = std::to_string(TheGame::Instance()->getGameScore());
		TheTextManager::Instance()->updateTexture(msg, "score");


	}

}

void PlayState::render()
{
	//��� �������� �� ���� �������� �������� m_loadingComplete
	if (m_loadingComplete)
	{
		if (pLevel != 0)
		{
			pLevel->render();
		}

		for (int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
		{
			TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
		}

		TheBulletHandler::Instance()->drawBullets();

		TheTextManager::Instance()->drawTexture("score");
		
	}
}

bool PlayState::onEnter()
{
	TheSoundManager::Instance()->playMusic(std::to_string(TheGame::Instance()->getCurrentLevel()), -1);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel(TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());

	TheTextureManager::Instance()->load("assets/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/lives.png", "lives", TheGame::Instance()->getRenderer());


	if (pLevel != 0)
	{
		m_loadingComplete = true;
	}

	std::string msg;
	msg = std::to_string(TheGame::Instance()->getGameScore());
	TheTextManager::Instance()->createTexture(msg, "score", TheGame::Instance()->getGameWidth() - 5,
		5, 200, 100, "second", 160, 30, 60, border::RIGHTBORDER);


	std::cout << "Entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	m_exiting = true;

	//delete pLevel;
	//pLevel = NULL;

	TheInputHandler::Instance()->reset();
	TheBulletHandler::Instance()->clearBullets();


	std::cout << "Exiting PlayState\n";
	return true;
}
