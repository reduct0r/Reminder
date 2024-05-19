#include "MainMenuState.h"
#include <iostream>
#include "../WelcomeScreen/WelcomeScreen.h"
#include "../../Game/GameState.h"
MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, Settings& gfxSettings)
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

MainMenuState::~MainMenuState() {
  auto it = this->buttons.begin();
  for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }
}

// INIT
void MainMenuState::InitVars() {
  this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_MAIN"].getSize().x;
}

void MainMenuState::InitBG() {
  float scale = this->scale;

  this->bg.setScale(sf::Vector2f(scale, scale));
  this->bg.setTexture(this->textures["BG_MAIN"]);

}

void MainMenuState::InitFonts() {
  if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf")) {
    throw ("WelcomeScreenState: COULD NOT LOAD FONT");
  }
}

void MainMenuState::InitButtons() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);

  float scale = this->scale;

  this->buttons["GITHUB_BTN"] =
      new ReminderUI::Button(winX / 2.0 - this->textures["GITHUB_ICON"].getSize().x * scale / 2.0,
                             winY / 1.25,
                             scale,
                             this->textures["GITHUB_ICON"],
                             this->textures["GITHUB_ICON"],
                             this->textures["GITHUB_ICON"]);

  this->buttons["SETTINGS_BTN"] = new ReminderUI::Button(winX - winX / 15,
                                                         winY / 50,
                                                         scale,
                                                         this->textures["SETTINGS_ICON"],
                                                         this->textures["SETTINGS_ICON"],
                                                         this->textures["SETTINGS_ICON"]);

  this->buttons["LOGOUT_BTN"] =
      new ReminderUI::Button(winX / 10 - this->textures["LOG_OUT"].getSize().x * scale / 2.0, winY * 0.05, scale,
                             this->textures["LOG_OUT"], this->textures["LOG_OUT2"], this->textures["LOG_OUT2"]);

  float mid = winX / 2.0 - this->textures["STARTGAME"].getSize().x * scale / 2.0;
  float yaw = winY / 2.0 - this->textures["STARTGAME"].getSize().y * scale / 2.0;

  this->buttons["GAME_BTN"] = new ReminderUI::Button(mid,
                                                     yaw - winY * 0.05,
                                                     scale,
                                                     this->textures["STARTGAME"],
                                                     this->textures["STARTGAME2"],
                                                     this->textures["STARTGAME2"]);

  this->buttons["PRESETS_BTN"] = new ReminderUI::Button(mid,
                                                        yaw + winY / 14.0,
                                                        scale,
                                                        this->textures["PRESETS"],
                                                        this->textures["PRESETS2"],
                                                        this->textures["PRESETS2"]);

  this->buttons["SETTINGS_BTN1"] = new ReminderUI::Button(mid,
                                                          yaw + winY / 5.2,
                                                          scale,
                                                          this->textures["SETTINGS"],
                                                          this->textures["SETTINGS2"],
                                                          this->textures["SETTINGS2"]);
}

void MainMenuState::InitTextures() {
  sf::Texture texture;
  texture.setSmooth(1);

  texture.loadFromFile("Resources/Textures/UI/Main Menu/Background.png");
  this->textures["BG_MAIN"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Github icon.png");
  this->textures["GITHUB_ICON"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/settings_button.png");
  this->textures["SETTINGS_ICON"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/Log_out1.png");
  this->textures["LOG_OUT"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/Log_out2.png");
  this->textures["LOG_OUT2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/start_game_button.png");
  this->textures["STARTGAME"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/start_game_button2.png");
  this->textures["STARTGAME2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/choose_preset_button.png");
  this->textures["PRESETS"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/choose_preset_button2.png");
  this->textures["PRESETS2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/settings_button1.png");
  this->textures["SETTINGS"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/settings_button2.png");
  this->textures["SETTINGS2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Main Menu/Logo reminder.png");
  this->textures["LOGO"] = texture;

}

void MainMenuState::InitSprites() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);
  float scale = this->scale;

  sf::Sprite sprite;
  sprite.setScale(scale, scale);
  sprite.setTexture(this->textures["LOGO"]);
  sprite.setPosition(winX / 2.0 - this->textures["LOGO"].getSize().x * scale / 2.05,
                     winY / 2.2 - this->textures["LOGO"].getSize().y * scale / 2.0 - winY / 5.0);
  this->sprites["LOGO"] = sprite;

}

// UPDATE
void MainMenuState::Update(const float &dt) {
  this->UpdateMousePos();
  this->UpdateKeyTime(dt);
  this->UpdateButtons();
  this->UpdateEvents();

  if (this->bg.getTexture()->getSize().x * this->scale != this->window->getSize().x) {
    this->InitTextures();
    this->InitVars();
    this->InitSprites();
    this->InitBG();
    this->InitFonts();
    this->InitButtons();
  }
}

void MainMenuState::UpdateButtons() {
  for (auto &it : this->buttons) {
    it.second->Update(this->MousePosView);
  }

  /* Обработка кнопок */
  if (this->buttons["SETTINGS_BTN"]->isPressed() and this->getKeyTime()) {
    this->states->push(new SettingsState(this->window, this->states, this->gfxSettings));
  }
  if (this->buttons["SETTINGS_BTN1"]->isPressed() and this->getKeyTime()) {
    this->states->push(new SettingsState(this->window, this->states, this->gfxSettings));
  }

  if (this->buttons["LOGOUT_BTN"]->isPressed() and this->getKeyTime()) {
    // ВЫЙТИ ИХЗ АККА

    this->states->push(new WelcomeScreenState(this->window, this->states, this->gfxSettings));
  }


  if (this->buttons["PRESETS_BTN"]->isPressed() and this->getKeyTime()) {

    this->states->push(new PresetsMenuState(this->window, this->states, this->gfxSettings));
  }

	if (this->buttons["GAME_BTN"]->isPressed() and this->getKeyTime())
	{
		this->states->push(new GameState(this->window, this->states, this->gfxSettings));
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

void MainMenuState::UpdateSprites() {
}

void MainMenuState::UpdateEvents() {
  while (this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) {
      this->window->close();
    }
  }
}

void MainMenuState::UpdateKeyBoardBinds(const float &dt) {
  this->CheckForQuit();
}

//RENDER
void MainMenuState::Render(sf::RenderTarget *target) {
  if (!target) {
    target = this->window;
  }

  target->draw(this->bg);
  this->RenderButtons(target);
  this->RenderSprites(target);

}

void MainMenuState::RenderButtons(sf::RenderTarget *target) {
  for (auto &it : this->buttons) {
    it.second->Render(target);
  }
}

void MainMenuState::RenderSprites(sf::RenderTarget *target) {
  for (auto &it : this->sprites) {
    target->draw(it.second);
  }
}

void MainMenuState::EndState() {
  std::cout << "ENDING...";
}