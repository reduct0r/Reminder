#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;


	this->ToQuit = false;
}

State::~State()
{

}

const bool State::getQuit() const
{
	return this->ToQuit;
}

void State::UpdateMousePos()
{
	this->MousePosScreen = sf::Mouse::getPosition();
	this->MousePosWindow = sf::Mouse::getPosition(*this->window);
	this->MousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
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
