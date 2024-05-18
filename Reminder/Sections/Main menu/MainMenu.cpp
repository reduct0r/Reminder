#include "MainMenu.h"

void MainMenu::InitVars() {
  this->window = nullptr;
  this->dt = 0;
}

void MainMenu::InitWindow() {
  if (this->gfxSettings.fullscreen) {
    this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                                        this->gfxSettings.title,
                                        sf::Style::Fullscreen,
                                        this->gfxSettings.contextSettings);
  } else {
    this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                                        this->gfxSettings.title,
                                        sf::Style::Titlebar | sf::Style::Close,
                                        this->gfxSettings.contextSettings);
  }

  this->window->setFramerateLimit(this->gfxSettings.frameLimit);
  this->window->setVerticalSyncEnabled(this->gfxSettings.VSync);
}

void MainMenu::InitStates() {
  this->states.push(new MainMenuState(this->window, &this->states, this->gfxSettings));
}

void MainMenu::InitSettings() {
  this->gfxSettings.LoadFromFile("Config/SFML SPECS.ini");
}

MainMenu::MainMenu() {
  this->InitSettings();
  this->InitWindow();
  this->InitStates();
}

MainMenu::~MainMenu() {
  delete this->window;

  while (!this->states.empty()) {
    delete this->states.top();
    this->states.pop();
  }
}

// FUNCTIONS

void MainMenu::Update() {
  this->UpdateEvents();

  if (!this->states.empty()) {
    this->states.top()->Update(this->dt);

    if (this->states.top()->getQuit()) {
      this->states.top()->EndState();
      delete this->states.top();
      this->states.pop();
    }
  } else {
    this->EndApplication(); // ДЕЙСТВИЕ ПЕРЕД ВЫХОДОМ
    this->window->close();
  }
}

void MainMenu::Render() {
  this->window->clear();

  if (!this->states.empty()) {
    this->states.top()->Render(this->window);
  }

  this->window->display();
}

void MainMenu::EndApplication() {
  // ДЕЛАЕМ ВСЕ ЧТО НУЖНО ПЕРЕД ТЕМ КАК ЗАКРЫТЬ ОКНО
  std::cout << "EXIT";
}

void MainMenu::Run() {
  while (this->window->isOpen()) {
    this->UpdateDT();
    this->Update();
    this->Render();
  }
}

void MainMenu::UpdateEvents() {
  while (this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) {
      this->window->close();
    }
  }
}

void MainMenu::UpdateDT() {
  this->dt = this->dtClock.restart().asSeconds();
}
