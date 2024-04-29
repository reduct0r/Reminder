#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->InitTextures();
	this->InitVars();
	this->InitSprites();
	this->InitBG();
	this->InitFonts();
	this->InitButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// INIT
void MainMenuState::InitVars()
{
	this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_MAIN"].getSize().x;
}

void MainMenuState::InitBG()
{
	float scale = this->scale;

	this->bg.setScale(sf::Vector2f(scale, scale));
	this->bg.setTexture(this->textures["BG_MAIN"]);

}

void MainMenuState::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf"))
	{
		throw("WelcomeScreenState: COULD NOT LOAD FONT");
	}
}

void MainMenuState::InitButtons()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);

	float scale = this->scale;
	float mid = 100;			//winX / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().x * scale / 2.0;
	float yaw = 100;			// winY / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().y * scale / 2.0;

	this->buttons["GITHUB_BTN"] = new UI::Button(winX / 2.0 - this->textures["GITHUB_ICON"].getSize().x * scale / 2.0, yaw + winY / 2.8, scale, scale, &this->font, sf::String(""), this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"]);
	this->buttons["SETTINGS_BTN"] = new UI::Button(winX - winX / 15, winY / 50, scale, scale, &this->font, sf::String(""), this->textures["SETTINGS_ICON"], this->textures["SETTINGS_ICON"], this->textures["SETTINGS_ICON"]);

}

void MainMenuState::InitTextures()
{
	sf::Texture texture;
	texture.setSmooth(1);

	texture.loadFromFile("Resources/Textures/UI/Main Menu/Background.png");
	this->textures["BG_MAIN"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Github icon.png");
	this->textures["GITHUB_ICON"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Main Menu/settings_button.png");
	this->textures["SETTINGS_ICON"] = texture;
}

void MainMenuState::InitSprites()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	//sf::Sprite sprite1;
	//sprite1.setScale(0, 0);
	//sprite1.setTexture(this->textures["LOGIN_FIELD"]);
	//sprite1.setPosition(winX / 2.0 - this->textures["LOGIN_FIELD"].getSize().x * scale / 2.0, winY / 4.0);
	//this->sprites["LOG_FIELD"] = sprite1;

}


// UPDATE 
void MainMenuState::Update(const float& dt)
{
	this->UpdateMousePos();
	this->UpdateKeyTime(dt);
	this->UpdateButtons();
	this->UpdateEvents();
}

void MainMenuState::UpdateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->Update(this->MousePosView);
	}

	/* Обработка кнопок */
	if (this->buttons["SETTINGS_BTN"]->isPressed())
	{
		this->states->push(new SettingsState(this->window, this->states));
	}
}

void MainMenuState::UpdateSprites()
{
}

void MainMenuState::UpdateEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void MainMenuState::UpdateKeyBoardBinds(const float& dt)
{
	this->CheckForQuit();
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
	this->RenderSprites(target);

}

void MainMenuState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void MainMenuState::RenderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites)
	{
		target->draw(it.second);
	}
}

void MainMenuState::EndState()
{
	std::cout << "ENDING...";
}