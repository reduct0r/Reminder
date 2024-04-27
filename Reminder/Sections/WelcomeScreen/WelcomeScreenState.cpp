#include "WelcomeScreenState.h"
#include <iostream>

WelcomeScreenState::WelcomeScreenState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->InitTextures();
	this->InitSprites();
	this->InitVars();
	this->InitBG();
	this->InitFonts();
	this->InitButtons();
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


void WelcomeScreenState::InitVars()
{
}

void WelcomeScreenState::InitBG()
{
	float scale = float(this->window->getSize().x) / this->textures["BG_WELCOME"].getSize().x;

	this->bg.setScale(sf::Vector2f(scale, scale));
	this->bg.setTexture(this->textures["BG_WELCOME"]);
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
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);

	float scale = winX / this->textures["BG_WELCOME"].getSize().x;
	float mid = winX / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().x * scale / 2.0;
	float yaw = winY / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().y * scale / 2.0;

	this->buttons["LOGIN_BTN"] = new UI::Button(mid, yaw + winY / 6.0, scale, scale, &this->font, sf::String(""), this->textures["LOGIN_BT_IDLE"], this->textures["LOGIN_BT_HOVER"], this->textures["LOGIN_BT_HOVER"]);

	this->buttons["REGISTER_BTN"] = new UI::Button(mid, yaw + winY / 30.0 , scale, scale, &this->font, sf::String(""), this->textures["REG_BT_IDLE"], this->textures["REG_BT_HOVER"], this->textures["REG_BT_HOVER"]);

	this->buttons["GITHUB_BTN"] = new UI::Button(winX / 2.0 - this->textures["GITHUB_ICON"].getSize().x * scale / 2.0, yaw + winY / 3.0, scale, scale, &this->font, sf::String(""), this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"]);
}


void WelcomeScreenState::InitTextures()
{
	sf::Texture texture;

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

}

void WelcomeScreenState::InitSprites()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = float(this->window->getSize().x) / this->textures["BG_WELCOME"].getSize().x;
	sf::Sprite sprite;
	sprite.setScale(scale, scale);

	sprite.setTexture(this->textures["LOGO"]);
	sprite.setPosition(winX / 2.0 - this->textures["LOGO"].getSize().x * scale / 2.05, winY / 2.0 - this->textures["LOGO"].getSize().y * scale / 2.0 - winY / 5.0);
	this->sprites["LOGO"] = sprite;
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
		it.second->Update(this->MousePosView);
	}

	//if (this->buttons["REGISTER_BTN"]->isPressed())
	//{
	//	this->ToQuit = 1;
	//}

	/* Обработка кнопок */

	if (this->buttons["LOGIN_BTN"]->isPressed())
	{
		this->states->push(new MainMenuState(this->window, this->states));
	}

	if (this->buttons["REGISTER_BTN"]->isPressed())
	{
	}

	if (this->buttons["GITHUB_BTN"]->isPressed())
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

void WelcomeScreenState::UpdateSprites()
{
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
	this->RenderSprites(target);
}

void WelcomeScreenState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void WelcomeScreenState::RenderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites)
	{
		target->draw(it.second);
	}
}
