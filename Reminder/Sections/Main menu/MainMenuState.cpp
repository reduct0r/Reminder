#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window)
	:State(window)
{
	this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->bg.setFillColor(sf::Color::Magenta);
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
	//if (!target)
	//{
	//	target = this->window;
	//}

	target->draw(this->bg);
}
