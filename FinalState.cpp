#include "FinalState.h"

const std::string FinalState::s_finalID = "FINAL";

void FinalState::update()
{
}

void FinalState::render()
{
}

bool FinalState::onEnter()
{




    std::cout << "Entering FinalState\n";
    return true;
}

bool FinalState::onExit()
{




    std::cout << "Exiting FinalState\n";
    return true;
}
