#include "PresetsMenuState.h"
#include <iostream>
#include "../WelcomeScreen/WelcomeScreen.h"

PresetsMenuState::PresetsMenuState(sf::RenderWindow* window, std::stack<State*>* states, Settings& gfxSettings)
	:State(window, states), gfxSettings(gfxSettings)
{
	this->InitTextures();
	this->InitVars();
	this->InitSprites();
	this->InitBG();
	this->InitFonts();
	this->InitButtons();

	this->startFullScreen = this->gfxSettings.fullscreen;
}

PresetsMenuState::~PresetsMenuState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// INIT
void PresetsMenuState::InitVars()
{
	this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_PRESETS"].getSize().x;
}

void PresetsMenuState::InitBG()
{
	float scale = this->scale;

	this->bg.setScale(sf::Vector2f(scale, scale));
	this->bg.setTexture(this->textures["BG_PRESETS"]);

}

void PresetsMenuState::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf"))
	{
		throw("PresetsState: COULD NOT LOAD FONT");
	}
}

void PresetsMenuState::InitButtons()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);

	float scale = this->scale;
	this->buttons["BACK_BTN"] = new  ReminderUI::Button(winY / 18, winY / 18, scale, scale, &this->font, sf::String(""), this->textures["BACK"], this->textures["BACK"], this->textures["BACK"]);

}

void PresetsMenuState::InitTextures()
{
	sf::Texture texture;
	texture.setSmooth(1);

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/back2.png");
	this->textures["BACK"] = texture;

	texture.loadFromFile("Resources/Textures/UI/PresetsMenu/Logo presets.png");
	this->textures["LOGO"] = texture;

	texture.loadFromFile("Resources/Textures/UI/PresetsMenu/Background.png");
	this->textures["BG_PRESETS"] = texture;

}

void PresetsMenuState::InitSprites()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	sf::Sprite sprite;
	sprite.setScale(scale, scale);
	sprite.setTexture(this->textures["LOGO"]);
	sprite.setPosition(winX / 2.0 - this->textures["LOGO"].getSize().x * scale / 2.05, winY / 3 - this->textures["LOGO"].getSize().y * scale / 2.0 - winY / 7.0);
	this->sprites["LOGO"] = sprite;

}


// UPDATE 
void PresetsMenuState::Update(const float& dt)
{
	this->UpdateMousePos();
	this->UpdateKeyTime(dt);
	this->UpdateButtons();
	this->UpdateEvents();

	if (this->bg.getTexture()->getSize().x * this->scale != this->window->getSize().x)
	{
		this->InitTextures();
		this->InitVars();
		this->InitSprites();
		this->InitBG();
		this->InitFonts();
		this->InitButtons();
	}
}

void PresetsMenuState::UpdateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->MousePosView);
	}

	/* Обработка кнопок */
	if (this->buttons["BACK_BTN"]->isPressed() and this->getKeyTime())
	{
		this->ToQuit = 1;
	}

}

void PresetsMenuState::UpdateSprites()
{
}

void PresetsMenuState::UpdateEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void PresetsMenuState::UpdateKeyBoardBinds(const float& dt)
{
	this->CheckForQuit();
}


//RENDER
void PresetsMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->bg);
	this->RenderButtons(target);
	this->RenderSprites(target);

}

void PresetsMenuState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void PresetsMenuState::RenderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites)
	{
		target->draw(it.second);
	}
}

void PresetsMenuState::EndState()
{
	std::cout << "ENDING...";
}