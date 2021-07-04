#include "MenuState.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{

}

void MenuState::render()
{

}

bool MenuState::onEnter()
{
	std::cout << "Entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	std::cout << "exiting MenuState\n";
	return true;
}
