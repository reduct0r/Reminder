#include "GameProcess.h"

void Game::InitVars() {
    this->window = nullptr;
    this->dt = 0;
}

void Game::InitWindow() {
    if (this->gfxSettings.fullscreen) {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Fullscreen,
            this->gfxSettings.contextSettings);
    }
    else {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.contextSettings);
    }

    this->window->setFramerateLimit(this->gfxSettings.frameLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.VSync);
}

void Game::InitStates() {
    this->states.push(new PresetsMenuState(this->window, &this->states, this->gfxSettings));
}

void Game::InitSettings() {
    this->gfxSettings.LoadFromFile("Config/SFML SPECS.ini");
}

Game::Game() {
    this->InitSettings();
    this->InitWindow();
    this->InitStates();
}

Game::~Game() {
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

// FUNCTIONS

void Game::Update() {
    this->UpdateEvents();

    if (!this->states.empty()) {
        this->states.top()->Update(this->dt);

        if (this->states.top()->getQuit()) {
            this->states.top()->EndState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->EndApplication(); 
        this->window->close();
    }
}

void Game::Render() {
    this->window->clear();

    if (!this->states.empty()) {
        this->states.top()->Render(this->window);
    }

    this->window->display();
}

void Game::EndApplication() 
{
}

void Game::Run() {
    while (this->window->isOpen()) {
        this->UpdateDT();
        this->Update();
        this->Render();
    }
}

void Game::UpdateEvents() {
    while (this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

void Game::UpdateDT() {
    this->dt = this->dtClock.restart().asSeconds();
}


namespace Reminder {
void init(Reminder::CardPreset &preset) {
  preset.shuffle();
}

bool menu(bool &answer, bool flag) {
  if (!flag) {
    std::cout << "1 - Right \t\t 0 - Wrong" << std::endl;
    std::cin >> answer;
    return answer;
  } else {
    std::cout << "1 - OK" << std::endl;
    std::cin >> answer;
    return answer;
  }
}

void run(Reminder::CardPreset &preset) {
  Reminder::CardPreset gamePreset(preset);

  init(gamePreset);

  bool answer = false;

  for (int i = 0; i < gamePreset.getLength(); ++i) {
    std::cout << gamePreset.getCardByIndex(i).getTitle() << std::endl;

    if (menu(answer, gamePreset.getCardByIndex(i).isFailed())) {
      gamePreset.getCardByIndex(i).setFailed(false);
      std::cout << gamePreset.getCardByIndex(i).getTitle() << " - ";
      std::cout << gamePreset.getCardByIndex(i).getText() << std::endl << std::endl;
    } else {
      gamePreset.getCardByIndex(i).setFailed(true);
      std::cout << "You are wrong" << std::endl << std::endl;
    }
  }

  for (int i = 0; i < gamePreset.getLength(); ++i) {
    if (gamePreset.getCardByIndex(i).isFailed()) {
      std::cout << gamePreset.getCardByIndex(i).getTitle() << " - ";
      std::cout << gamePreset.getCardByIndex(i).getText() << std::endl;

      if (menu(answer, gamePreset.getCardByIndex(i).isFailed())) {
        std::cout << "I hope you remember me now!" << std::endl << std::endl;
      } else {
        std::cerr << "Error ocurred :(" << std::endl << std::endl;
      }
    } else {
      continue;
    }
  }
}
}