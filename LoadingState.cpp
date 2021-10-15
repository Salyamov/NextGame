#include "LoadingState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "Game.h"
#include "InputHandler.h"
#include "SoundManger.h"
#include "TextManager.h"

const std::string LoadingState::s_loadingID = "LOADING";

void LoadingState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	}

	//TheTextManager::Instance()->updateTexture(...);
	/*
		(name, msg)
	*/
}

void LoadingState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	/*
	SDL_RenderCopy(TheGame::Instance()->getRenderer(), message, NULL, &messageRect);
	*/

	TheTextManager::Instance()->drawTexture("level");
	/*
		(name)
	*/

}

bool LoadingState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_loadingID, &m_gameObjects, &m_textureIDList);

	TheSoundManager::Instance()->stopMusic();

	/*
	//test initialization
	testFont = TTF_OpenFont("assets/Quicksilver.ttf", 24);
	if (testFont == NULL)
	{
		std::cout << "font doesn't loaded\n";
	}
	testColor = { 150, 150, 255 };
	
	std::string msg = "Level: ";
	msg += std::to_string(TheGame::Instance()->getCurrentLevel());
	textSurface = TTF_RenderText_Solid(testFont, msg.c_str(), testColor);
	message = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), textSurface);
	messageRect.x = 200;
	messageRect.y = 250;
	messageRect.w = 200;
	messageRect.h = 50;
	*/

	std::string msg = "Level: ";
	msg += std::to_string(TheGame::Instance()->getCurrentLevel());
	TheTextManager::Instance()->registerFont("assets/Quicksilver.ttf", "silver", 24);
	TheTextManager::Instance()->createTexture(msg, "level", 200, 250, 200, 50, "silver", 150, 150, 255);
	/*
		(msg, name, x, y, w, h, font, r, g, b); name - имя по которой можно получить доступ к созданной текстуре
	*/

	std::cout << "Entering LoadingState\n";

	return true;
}

bool LoadingState::onExit()
{

	//TheSoundManager::Instance()->playMusic(std::to_string(TheGame::Instance()->getCurrentLevel()), -1);

	std::cout << "Exiting LoadingState\n";

	//free test surface and texture
	/*
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(message);
	*/
	return true;
}

void LoadingState::s_loadingToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
