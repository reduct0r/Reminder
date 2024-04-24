#include "State.h"

State::State(sf::RenderWindow* window)
{
	this->window = window;
	this->ToQuit = false;
}

State::~State()
{

}

const bool State::getQuit() const
{
	return this->ToQuit;
}

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->ToQuit = 1;
	}
}

void State::EndState()
{
}
