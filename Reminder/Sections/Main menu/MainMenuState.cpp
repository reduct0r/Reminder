#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window)
	:State(window)
{

}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::UpdateKeyBoardBinds(const float& dt)
{
	this->CheckForQuit();
}

void MainMenuState::EndState()
{
	std::cout << "ENDING...";
}

void MainMenuState::Update(const float& dt)
{
	this->UpdateKeyBoardBinds(dt);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "KEY";
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{

}
