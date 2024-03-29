#include "FinalState.h"
#include "StateParser.h"
#include "TextManager.h"
#include "Game.h"
#include "SoundManger.h"

const std::string FinalState::s_finalID = "FINAL";

void FinalState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void FinalState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
    TheTextManager::Instance()->drawTexture("finalscore");
}

bool FinalState::onEnter()
{
    TheSoundManager::Instance()->playMusic(std::to_string(TheGame::Instance()->getCurrentLevel()), -1);

    StateParser stateParser;
    stateParser.parseState("assets/test.xml", s_finalID, &m_gameObjects, &m_textureIDList);

    std::string msg;
    msg = std::to_string(TheGame::Instance()->getGameScore());
    TheTextManager::Instance()->createTexture(msg, "finalscore", 225, 300, 250, 50, "silver", 120, 170, 255, LEFTBORDER);


    std::cout << "Entering FinalState\n";
    return true;
}

bool FinalState::onExit()
{




    std::cout << "Exiting FinalState\n";
    return true;
}
