#include "PresetsMenu.h"

void PresetsMenu::InitVars() {
  this->window = nullptr;
  this->dt = 0;
}

void PresetsMenu::InitWindow() {
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

void PresetsMenu::InitStates() {
  this->states.push(new PresetsMenuState(this->window, &this->states, this->gfxSettings));
}

void PresetsMenu::InitSettings() {
  this->gfxSettings.LoadFromFile("Config/SFML SPECS.ini");
}

PresetsMenu::PresetsMenu() {
  this->InitSettings();
  this->InitWindow();
  this->InitStates();
}

PresetsMenu::~PresetsMenu() {
  delete this->window;

  while (!this->states.empty()) {
    delete this->states.top();
    this->states.pop();
  }
}

// FUNCTIONS

void PresetsMenu::Update() {
  this->UpdateEvents();

  if (!this->states.empty()) {
    this->states.top()->Update(this->dt);

    if (this->states.top()->getQuit()) {
      this->states.top()->EndState();
      delete this->states.top();
      this->states.pop();
    }
  } else {
    this->EndApplication(); // �������� ����� �������
    this->window->close();
  }
}

void PresetsMenu::Render() {
  this->window->clear();

  if (!this->states.empty()) {
    this->states.top()->Render(this->window);
  }

  this->window->display();
}

void PresetsMenu::EndApplication() {
  // ������ ��� ��� ����� ����� ��� ��� ������� ����
}

void PresetsMenu::Run() {
  while (this->window->isOpen()) {
    this->UpdateDT();
    this->Update();
    this->Render();
  }
}

void PresetsMenu::UpdateEvents() {
  while (this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) {
      this->window->close();
    }
  }
}

void PresetsMenu::UpdateDT() {
  this->dt = this->dtClock.restart().asSeconds();
}
