#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{

}

SettingsState::~SettingsState()
{
}

// INIT
void SettingsState::InitVars()
{
	this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_WELCOME"].getSize().x;
}

void SettingsState::InitBG()
{
	float scale = this->scale;

	this->bg.setScale(sf::Vector2f(scale, scale));
	this->bg.setTexture(this->textures["BG_WELCOME"]);
}

void SettingsState::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf"))
	{
		throw("WelcomeScreenState: COULD NOT LOAD FONT");
	}
}

void SettingsState::InitButtons()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	this->buttons["GITHUB_BTN"] = new UI::Button(winX / 2.0 - this->textures["GITHUB_ICON"].getSize().x * scale / 2.0, 50 + winY / 2.8, scale, scale, &this->font, sf::String(""), this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"]);
	this->buttons["BACK_BTN"] = new UI::Button(30, 30, scale, scale, &this->font, sf::String(""), this->textures["BACK"], this->textures["BACK"], this->textures["BACK"]);
	this->buttons["BACK_BTN"]->Hide(1);

}

void SettingsState::InitTextures()
{
	sf::Texture texture;
	texture.setSmooth(1);

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Background.png");
	this->textures["BG_WELCOME"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button first.png");
	this->textures["LOGIN_BT_IDLE"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button second.png");
	this->textures["LOGIN_BT_HOVER"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Reg button first.png");
	this->textures["REG_BT_IDLE"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Reg button second.png");
	this->textures["REG_BT_HOVER"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Github icon.png");
	this->textures["GITHUB_ICON"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Logo reminder.png");
	this->textures["LOGO"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/login.png");
	this->textures["LOGIN_FIELD"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/password.png");
	this->textures["PASSWORD_FIELD"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/back2.png");
	this->textures["BACK"] = texture;

}

void SettingsState::InitSprites()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	sf::Sprite sprite1;
	sprite1.setScale(0, 0);
	sprite1.setTexture(this->textures["LOGIN_FIELD"]);
	sprite1.setPosition(winX / 2.0 - this->textures["LOGIN_FIELD"].getSize().x * scale / 2.0, winY / 4.0);
	this->sprites["LOG_FIELD"] = sprite1;

	sf::Sprite sprite3;
	sprite3.setScale(0, 0);
	sprite3.setTexture(this->textures["PASSWORD_FIELD"]);
	sprite3.setPosition(winX / 2.0 - this->textures["PASSWORD_FIELD"].getSize().x * scale / 2.0, winY / 4.0);
	this->sprites["PASS_FIELD"] = sprite3;

	sf::Sprite sprite;
	sprite.setScale(scale, scale);
	sprite.setTexture(this->textures["LOGO"]);
	sprite.setPosition(winX / 2.0 - this->textures["LOGO"].getSize().x * scale / 2.05, winY / 2.0 - this->textures["LOGO"].getSize().y * scale / 2.0 - winY / 5.0);
	this->sprites["LOGO"] = sprite;


}


// UPDATE 
void  SettingsState::Update(const float& dt)
{
	this->UpdateMousePos();
	this->UpdateKeyTime(dt);
	this->UpdateButtons();
	this->UpdateEvents();

}

void  SettingsState::UpdateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->MousePosView);
	}

	//if (this->buttons["REGISTER_BTN"]->isPressed())
	//{
	//	this->ToQuit = 1;
	//}

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
