#include "SettingsState.h"
#include <iostream>

SettingsState::SettingsState(sf::RenderWindow* window, std::stack<State*>* states, Settings& gfxSettings)
	:State(window, states), gfxSettings(gfxSettings)
{
	this->InitTextures();
	this->InitVars();
	this->InitSprites();
	this->InitBG();
	this->InitFonts();
	this->InitButtons();
	this->InitDropDownLists();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (auto it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

// INIT
void SettingsState::InitVars()
{
	this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_SETTINGS"].getSize().x;

	this->videoModes = {
		sf::VideoMode(960, 540),
		sf::VideoMode(960, 540),
		sf::VideoMode(1024, 576),
		sf::VideoMode(1152, 648),
		sf::VideoMode(1280, 720),
		sf::VideoMode(1366, 768),
		sf::VideoMode(1600, 900),
		sf::VideoMode(1920, 1080),
		sf::VideoMode(2560, 1440),
		sf::VideoMode(3840, 2160),
		sf::VideoMode(7680, 4320)
	};
}

void SettingsState::InitBG()
{
	float scale = this->scale;

	this->bg.setScale(sf::Vector2f(scale, scale));
	this->bg.setTexture(this->textures["BG_SETTINGS"]);
}

void SettingsState::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/BRLNSR.ttf"))
	{
		throw("WelcomeScreenState: COULD NOT LOAD FONT");
	}
}

void SettingsState::InitButtons()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	this->buttons["GITHUB_BTN"] = new ReminderUI::Button(winX / 1.05 - this->textures["GITHUB_ICON"].getSize().x * scale / 2.0, winY / 1.05 - this->textures["GITHUB_ICON"].getSize().y * scale, scale, scale, &this->font, sf::String(""), this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"]);
	this->buttons["BACK_BTN"] = new ReminderUI::Button(winX / 80, winY / 50, scale, scale, &this->font, sf::String(""), this->textures["BACK"], this->textures["BACK"], this->textures["BACK"]);
	this->buttons["APPLY_BTN"] = new ReminderUI::Button(winX / 2 - this->textures["APPLY_IDL"].getSize().x * scale / 2.0, winY / 1.2, scale, scale, &this->font, sf::String(""), this->textures["APPLY_IDL"], this->textures["APPLY_HVR"], this->textures["APPLY_HVR"]);
	
	if (!this->gfxSettings.fullscreen)
	{
		this->buttons["FULLSCREEN_BTN"] = new ReminderUI::Button(winX / 2 - this->textures["FULLSCREEN_MODE"].getSize().x * scale / 2.0, winY / 2, scale, scale, &this->font,
                                                                 sf::String(""), this->textures["FULLSCREEN_MODE"], this->textures["FULLSCREEN_MODE2"], this->textures["FULLSCREEN_MODE2"]);
	}
	else
	{
		this->buttons["FULLSCREEN_BTN"] = new ReminderUI::Button(winX / 2 - this->textures["WINDOW_MODE"].getSize().x * scale / 2.0, winY / 2, scale, scale, &this->font,
                                                                 sf::String(""), this->textures["WINDOW_MODE"], this->textures["WINDOW_MODE2"], this->textures["WINDOW_MODE2"]);
	}

	if (!this->gfxSettings.sound)
	{
		this->buttons["SOUND_BTN"] = new ReminderUI::Button(winX / 2 - this->textures["SOUND_ON"].getSize().x * scale / 2.0, winY / 3, scale, scale, &this->font,
                                                            sf::String(""), this->textures["SOUND_ON"], this->textures["SOUND_ON2"], this->textures["SOUND_ON2"]);
	}
	else
	{
		this->buttons["SOUND_BTN"] = new ReminderUI::Button(winX / 2 - this->textures["SOUND_OFF"].getSize().x * scale / 2.0, winY / 3, scale, scale, &this->font,
                                                            sf::String(""), this->textures["SOUND_OFF"], this->textures["SOUND_OFF2"], this->textures["SOUND_OFF2"]);
	}
}

void SettingsState::InitTextures()
{
	sf::Texture texture;
	texture.setSmooth(1);

	texture.loadFromFile("Resources/Textures/UI/Settings/Background.png");
	this->textures["BG_SETTINGS"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Github icon.png");
	this->textures["GITHUB_ICON"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Logo reminder.png");
	this->textures["LOGO"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Resolution.png");
	this->textures["DDL_MAIN"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Rectangle_20.png");
	this->textures["DDL_SECOND"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Rectangle_21.png");
	this->textures["DDL_SECOND_HOVER"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Apply1.png");
	this->textures["APPLY_IDL"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Apply2.png");
	this->textures["APPLY_HVR"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/back2.png");
	this->textures["BACK"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/fullscreen.png");
	this->textures["FULLSCREEN_MODE"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/fullscreen2.png");
	this->textures["FULLSCREEN_MODE2"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/to_window.png");
	this->textures["WINDOW_MODE"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/to_window2.png");
	this->textures["WINDOW_MODE2"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Volume on.png");
	this->textures["SOUND_ON"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Volume on2.png");
	this->textures["SOUND_ON2"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Volume_off.png");
	this->textures["SOUND_OFF"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Settings/Volume_off2.png");
	this->textures["SOUND_OFF2"] = texture;
}
void SettingsState::InitSprites()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

}

void SettingsState::InitDropDownLists()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	std::vector<std::string> l = {"Resolution", "960 x 540", "1024 x 576", "1152 x 648", "1280 x 720 (HD)", "1366 x 768", "1600 x 900", "1920 x 1080 (FHD)", "2560 x 1440 (QHD)", "3840 x 2160 (4K)", "7680 x 4320 (8K)" };
	
	/*std::vector<std::string> modes_str;
	
	for (auto& i : this->videoModes)
	{
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}*/

	this->dropDownLists["RESOLUTION"] = new ReminderUI::DropDownList(this->scale / 1.5, 0, winX / 3.2 - this->textures["DDL_MAIN"].getSize().x * scale / 2 , 0, &this->font, 25, l, this->textures["DDL_SECOND"],
                                                                     this->textures["DDL_SECOND_HOVER"], this->textures["DDL_MAIN"]);
}


// UPDATE 
void  SettingsState::Update(const float& dt)
{
	this->UpdateMousePos();
	this->UpdateKeyTime(dt);
	this->UpdateButtons();
	this->UpdateEvents();
	this->UpdateDropDownLists(dt);

}

void  SettingsState::UpdateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->MousePosView);
	}

	if (this->buttons["BACK_BTN"]->isPressed())
	{
		this->ToQuit = 1;
	}

	if (this->buttons["SOUND_BTN"]->isPressed() and this->getKeyTime())
	{
		if (this->gfxSettings.sound == 0)
		{
			this->gfxSettings.sound = 1;
			this->buttons["SOUND_BTN"]->setNewTextures(this->textures["SOUND_OFF"], this->textures["SOUND_OFF2"], this->textures["SOUND_OFF2"]);
		}
		else
		{
			this->gfxSettings.sound = 0;
			this->buttons["SOUND_BTN"]->setNewTextures(this->textures["SOUND_ON"], this->textures["SOUND_ON2"], this->textures["SOUND_ON2"]);
		}
	}

	if (this->buttons["FULLSCREEN_BTN"]->isPressed() and this->getKeyTime())
	{
		if (this->gfxSettings.fullscreen == 0)
		{
			this->gfxSettings.fullscreen = 1;
			this->buttons["FULLSCREEN_BTN"]->setNewTextures(this->textures["WINDOW_MODE"], this->textures["WINDOW_MODE2"], this->textures["WINDOW_MODE2"]);
		}
		else
		{
			this->gfxSettings.fullscreen = 0;
			this->buttons["FULLSCREEN_BTN"]->setNewTextures(this->textures["FULLSCREEN_MODE"], this->textures["FULLSCREEN_MODE2"], this->textures["FULLSCREEN_MODE2"]);
		}
	}


	if (this->buttons["APPLY_BTN"]->isPressed() and this->getKeyTime())
	{
		// !!!
		this->gfxSettings.resolution = this->videoModes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
		
		if (this->gfxSettings.fullscreen)
		{
			this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);
		}
		else
		{
			this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
		}

		this->window->setFramerateLimit(this->gfxSettings.frameLimit);
		this->window->setVerticalSyncEnabled(this->gfxSettings.VSync);

		this->gfxSettings.SaveToFile("Config/SFML SPECS.ini");
		
		this->InitTextures();
		this->InitVars();
		this->InitSprites();
		this->InitBG();
		this->InitFonts();
		this->InitButtons();
		this->InitDropDownLists();

		
	}

	if (this->buttons["GITHUB_BTN"]->isPressed() and this->getKeyTime())
	{
		std::string url = "https://github.com/reduct0r/Reminder";

		#ifdef _WIN32
		std::string command = "start " + url + ""; // Для Windows
		#elif __APPLE__
		std::string command = "open " + url + ""; // Для macOS
		#endif

		// Вызываем командную строку сформированной команды
		system(command.c_str());
	}
}

void SettingsState::UpdateSprites()
{
}

void SettingsState::UpdateEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void SettingsState::UpdateKeyBoardBinds(const float& dt)
{
	this->CheckForQuit();
}

void SettingsState::UpdateDropDownLists(const float& dt)
{
	for (auto& it : this->dropDownLists)
	{
		it.second->Update(this->MousePosView, dt);
	}
}


//RENDER
void SettingsState::Render(sf::RenderTarget* target)
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

void SettingsState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void SettingsState::RenderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites)
	{
		target->draw(it.second);
	}
}

void SettingsState::RenderDropDownLists(sf::RenderTarget* target)
{
	for (auto& it : this->dropDownLists)
	{
		it.second->Render(target);
	}
}
