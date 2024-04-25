#include "WelcomeScreenState.h"
#include <iostream>

WelcomeScreenState::WelcomeScreenState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->InitFonts();
	this->InitTextures();
	this->InitButtons();


	this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->bg.setFillColor(sf::Color::Magenta);
}

WelcomeScreenState::~WelcomeScreenState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void WelcomeScreenState::UpdateKeyBoardBinds(const float& dt)
{
	this->CheckForQuit();
}

void WelcomeScreenState::EndState()
{
	std::cout << "Welcome Screen ENDING...";
}


void WelcomeScreenState::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf"))
	{
		throw("WelcomeScreenState: COULD NOT LOAD FONT");
	}
}

void WelcomeScreenState::InitButtons()
{
	sf::Texture T1;
	T1.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button first.png");
	sf::Texture T2;
	T2.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button second.png");



	this->buttons["GO_TO_MAINMENU_BTN"] = new UI::Button(100, 100, 0.5, 0.5, &this->font, sf::String(""), this->textures["LOGIN_BT_IDLE"], this->textures["LOGIN_BT_HOVER"], this->textures["LOGIN_BT_HOVER"]);

	this->buttons["EXIT_BTN"] = new UI::Button(200, 500, 0.5, 0.5, &this->font, sf::String(""), T1, T2, T2);
}


void WelcomeScreenState::InitTextures()
{
	sf::Texture texture;
	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button first.png");
	this->textures["LOGIN_BT_IDLE"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button second.png");
	this->textures["LOGIN_BT_HOVER"] = texture;
}

// UPDATE 
void WelcomeScreenState::Update(const float& dt)
{
	this->UpdateMousePos();
	this->UpdateButtons();
}

void WelcomeScreenState::UpdateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->MousePosView, 1, 1, 1);
	}

	/* Обработка кнопок */

	if (this->buttons["GO_TO_MAINMENU_BTN"]->isPressed())
	{
		this->states->push(new MainMenuState(this->window, this->states));
	}



	if (this->buttons["EXIT_BTN"]->isPressed())
	{
		this->ToQuit = 1;
	}
}

//RENDER
void WelcomeScreenState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->bg);
	this->RenderButtons(target);
}

void WelcomeScreenState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}
