#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;


	this->ToQuit = false;
	this->keyTime = 0;
	this->keyTimeMax = 10;
}

State::~State()
{

}

const bool State::getQuit() const
{
	return this->ToQuit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0;
		return true;
	}
	return false;
}

void State::UpdateMousePos()
{
	this->MousePosScreen = sf::Mouse::getPosition();
	this->MousePosWindow = sf::Mouse::getPosition(*this->window);
	this->MousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::UpdateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10 * dt;
	}

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
