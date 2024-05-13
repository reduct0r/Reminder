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
	this->InitDropDownLists();

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
	this->buttons["MY_PRESETS_BTN"] = new  ReminderUI::Button(winX / 3.2 - this->textures["MY_PRESETS"].getSize().x * this->scale / 2,
		winY / 2 - this->textures["MY_PRESETS"].getSize().y * this->scale / 2, scale, scale, &this->font, sf::String(""),
		this->textures["MY_PRESETS"], this->textures["MY_PRESETS"], this->textures["MY_PRESETS"]);

	this->buttons["NEW_PRESET_BTN"] = new  ReminderUI::Button(winX / 1.5 - this->textures["NEW_PRESET"].getSize().x * this->scale / 2,
		winY / 2 - this->textures["MY_PRESETS"].getSize().y * this->scale / 2, scale, scale, &this->font, sf::String(""),
		this->textures["NEW_PRESET"], this->textures["NEW_PRESET"], this->textures["NEW_PRESET"]);

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

	texture.loadFromFile("Resources/Textures/UI/PresetsMenu/field my presets and counter.png");
	this->textures["MY_PRESETS"] = texture;

	texture.loadFromFile("Resources/Textures/UI/PresetsMenu/field new preset.png");
	this->textures["NEW_PRESET"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Resolution.png");
	this->textures["DDL_MAIN"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Rectangle_20.png");
	this->textures["DDL_SECOND"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Rectangle_21.png");
	this->textures["DDL_SECOND_HOVER"] = texture;

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

void PresetsMenuState::InitDropDownLists()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	std::vector<std::string> l = { "Choose preset", "PRESET1", "PRESET2", "PRESET3", "PRESET4" };

	this->dropDownLists["PRESETS_LIST"] = new ReminderUI::DropDownList(this->scale / 1.5, 0, winX / 1.4 - this->textures["DDL_SECOND"].getSize().x * scale / 2,
		winY / 3 - this->textures["DDL_SECOND"].getSize().y * scale / 2, &this->font, 25, l, this->textures["DDL_SECOND"], this->textures["DDL_SECOND_HOVER"],
		this->textures["DDL_SECOND"]);
	this->dropDownLists["PRESETS_LIST"]->Hide(1, this->scale / 1.5);
}


// UPDATE 
void PresetsMenuState::Update(const float& dt)
{
	this->UpdateMousePos();
	this->UpdateKeyTime(dt);
	this->UpdateButtons();
	this->UpdateEvents();
	this->UpdateDropDownLists(dt);

	if (this->bg.getTexture()->getSize().x * this->scale != this->window->getSize().x)
	{
		this->InitTextures();
		this->InitVars();
		this->InitSprites();
		this->InitBG();
		this->InitFonts();
		this->InitButtons();
		this->InitDropDownLists();
	}
}

void PresetsMenuState::UpdateDropDownLists(const float& dt)
{
	for (auto& it : this->dropDownLists)
	{
		it.second->Update(this->MousePosView, dt);
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

	if (this->buttons["MY_PRESETS_BTN"]->isPressed() and this->getKeyTime())
	{
		this->buttons["NEW_PRESET_BTN"]->Hide(1, this->scale);
		this->buttons["MY_PRESETS_BTN"]->setText("\n\nClick to return");
		this->dropDownLists["PRESETS_LIST"]->Hide(0, this->scale / 1.5);
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
	this->RenderDropDownLists(target);

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

void PresetsMenuState::RenderDropDownLists(sf::RenderTarget* target)
{
	for (auto& it : this->dropDownLists)
	{
		it.second->Render(target);
	}
}

void PresetsMenuState::EndState()
{
	std::cout << "ENDING...";
}