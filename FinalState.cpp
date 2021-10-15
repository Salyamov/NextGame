#include "FinalState.h"
#include "StateParser.h"

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
}

bool FinalState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("test.xml", s_finalID, &m_gameObjects, &m_textureIDList);



    std::cout << "Entering FinalState\n";
    return true;
}

bool FinalState::onExit()
{




    std::cout << "Exiting FinalState\n";
    return true;
}
