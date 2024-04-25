#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->InitFonts();
	this->InitFonts();
	this->InitButtons();


	this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->bg.setFillColor(sf::Color::White);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::UpdateKeyBoardBinds(const float& dt)
{
	this->CheckForQuit();
}

void MainMenuState::EndState()
{
	std::cout << "ENDING...";
}


void MainMenuState::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf"))
	{
		throw("MainMenuState: COULD NOT LOAD FONT");
	}
}

void MainMenuState::InitButtons()
{
	sf::Texture T1;
	T1.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button first.png");
	sf::Texture T2;
	T2.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button second.png");



	this->buttons["GAME_STATE_BTN"] = new UI::Button(250, 100, 0.5, 0.5, &this->font, sf::String("STATE_BTN"), T1, T2, T2);

	this->buttons["GAME_STATE_BTN2"] = new UI::Button(250, 500, 0.5, 0.5, &this->font, sf::String("STATE_BTN2"), T1, T2, T2);
}

// UPDATE 
void MainMenuState::Update(const float& dt)
{
	this->UpdateMousePos();
	this->UpdateButtons();
}

void MainMenuState::UpdateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->Update(this->MousePosView);
	}

	/* Обработка кнопок */
	if (this->buttons["GAME_STATE_BTN2"]->isPressed())
	{
		this->ToQuit = 1;
	}
}

//RENDER
void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->bg);
	this->RenderButtons(target);
}

void MainMenuState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}
