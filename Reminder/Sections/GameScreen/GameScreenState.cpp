﻿#include "GameScreenState.h"
#include <iostream>
#include "../WelcomeScreen/WelcomeScreen.h"

GameState::GameState(sf::RenderWindow *window,
                     std::stack<State *> *states,
                     Settings &gfxSettings,
                     std::vector<Reminder::CardPreset> &userPresets,
                     Reminder::CardPreset &activePreset,
                     Reminder::Database *database,
                     UserDAO &existingUser) : State(window, states),
                                              gfxSettings(gfxSettings),
                                              userPresets(userPresets),
                                              activePreset(activePreset),
                                              database(database),
                                              existingUser(existingUser) {
  this->InitTextures();
  this->InitVars();
  this->InitSprites();
  this->InitBG();
  this->InitFonts();
  this->InitButtons();
  this->InitDropDownLists();
  this->InitTexts();

  this->startFullScreen = this->gfxSettings.fullscreen;
}

GameState::~GameState() {
  auto it = this->buttons.begin();
  for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }

  auto it2 = this->dropDownLists.begin();
  for (auto it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it) {
    delete it2->second;
  }
}

// INIT
void GameState::InitVars() {
  this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_GAME"].getSize().x;

  for (int i = activePreset.getLength() - 1; i >= 0; --i) {
    awaitingCardsIndexes.push_back(i);
  }

}

void GameState::InitBG() {
  float scale = this->scale;

  this->bg.setScale(sf::Vector2f(scale, scale));
  this->bg.setTexture(this->textures["BG_GAME"]);

}

void GameState::InitFonts() {
  if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf")) {
    throw ("GAMEState: COULD NOT LOAD FONT");
  }
}

void GameState::InitButtons() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);
  float scale = this->scale;

  this->buttons["BACK_BTN"] = new ReminderUI::Button(winY / 18,
                                                     winY / 18,
                                                     scale,
                                                     this->textures["BACK"],
                                                     this->textures["BACK"],
                                                     this->textures["BACK"]);

  this->buttons["SWIPE_RIGHT_BTN"] = new ReminderUI::Button(winX / 2.4,
                                                            winY / 1.32,
                                                            scale,
                                                            this->textures["ARROW_RIGHT"],
                                                            this->textures["ARROW_RIGHT"],
                                                            this->textures["ARROW_RIGHT"]);

  this->buttons["SWIPE_LEFT_BTN"] = new ReminderUI::Button(winX / 6.5,
                                                           winY / 1.32,
                                                           scale,
                                                           this->textures["ARROW_LEFT"],
                                                           this->textures["ARROW_LEFT"],
                                                           this->textures["ARROW_LEFT"]);

  this->buttons["AWAITING_BTN"] =
      new ReminderUI::Button(0,
                             this->scale * 40,
                             winX / 1.55,
                             winY / 1.9,
                             scale,
                             scale,
                             &this->font,
                             "",
                             this->textures["AWAITING_CARDS"],
                             this->textures["AWAITING_CARDS"],
                             this->textures["AWAITING_CARDS"]);

  this->buttons["FAILED_BTN"] =
      new ReminderUI::Button(0,
                             this->scale * 40,
                             winX / 1.55,
                             winY / 6,
                             scale,
                             scale,
                             &this->font,
                             "",
                             this->textures["FAILED_CARDS"],
                             this->textures["FAILED_CARDS"],
                             this->textures["FAILED_CARDS"]);

  this->buttons["ACTIVE_CARD_BTN"] =
      new ReminderUI::Button(0,
                             this->scale * 40,
                             winX / 7.5,
                             winY / 3.6,
                             scale,
                             scale,
                             &this->font,
                             "",
                             this->textures["ACTIVE_CARD"],
                             this->textures["ACTIVE_CARD_HOVER"],
                             this->textures["ACTIVE_CARD_HOVER"]);
}

void GameState::InitTextures() {
  sf::Texture texture;
  texture.setSmooth(1);

  texture.loadFromFile("Resources/Textures/UI/Welcome Screen/back2.png");
  this->textures["BACK"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/Logo reminder mini.png");
  this->textures["LOGO"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/Background.png");
  this->textures["BG_GAME"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/arrow rigrt.png");
  this->textures["ARROW_RIGHT"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/arrow left.png");
  this->textures["ARROW_LEFT"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/awaiting cards.png");
  this->textures["AWAITING_CARDS"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/failed cards.png");
  this->textures["FAILED_CARDS"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/Active Card.png");
  this->textures["ACTIVE_CARD"] = texture;

  texture.loadFromFile("Resources/Textures/UI/Game/Intuitive.png");
  this->textures["ACTIVE_CARD_HOVER"] = texture;

}

void GameState::InitSprites() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);
  float scale = this->scale;

  sf::Sprite sprite;
  sprite.setScale(scale, scale);
  sprite.setTexture(this->textures["LOGO"]);
  sprite.setPosition(winX / 4.5, winY / 8.5);
  this->sprites["LOGO"] = sprite;

}

void GameState::InitDropDownLists() {

}

void GameState::InitTexts() {
  awaitingCardsIndexes.pop_back();
  sf::Text text;
  text.setFont(this->font);
  text.setFillColor(sf::Color::Black);
  text.setCharacterSize(this->scale * 40);

  text.setString(std::to_string(failedCardsIndexes.size()));
  text.setPosition(this->window->getSize().x / 1.18, this->window->getSize().y / 5.1);
  this->texts["COUNTER_FAILED"] = text;

  text.setString(std::to_string(awaitingCardsIndexes.size()));
  text.setPosition(this->window->getSize().x / 1.18, this->window->getSize().y / 1.8);
  this->texts["COUNTER_AWAITING"] = text;

  // Инициализация активной карточки и всего для нее
  // Титул ТОЛЬКО  для первой карточки сюда
  // Initialize the active card and everything for it
  // Title ONLY for the first card here

  GameState::showCardText(activePreset.getCardByIndex(currentCardIndex).getTitle());

}

// UPDATE
void GameState::Update(const float &dt) {
  this->UpdateMousePos();
  this->UpdateKeyTime(dt);
  this->UpdateButtons();
  this->UpdateEvents();
  this->UpdateDropDownLists(dt);

  if (this->bg.getTexture()->getSize().x * this->scale != this->window->getSize().x) {
    this->InitTextures();
    this->InitVars();
    this->InitSprites();
    this->InitBG();
    this->InitFonts();
    this->InitButtons();
    this->InitDropDownLists();
    this->InitTexts();
  }
}

void GameState::UpdateDropDownLists(const float &dt) {
  for (auto &it : this->dropDownLists) {
    it.second->Update(this->MousePosView, dt);
  }
}

void GameState::showCurrentCard() {
  sf::Text text;
  text.setFont(this->font);
  text.setFillColor(sf::Color::Black);
  text.setCharacterSize(this->scale * 40);

  text.setString(std::to_string(failedCardsIndexes.size()));
  text.setPosition(this->window->getSize().x / 1.18, this->window->getSize().y / 5.1);
  this->texts["COUNTER_FAILED"] = text;

  text.setString(std::to_string(awaitingCardsIndexes.size()));
  text.setPosition(this->window->getSize().x / 1.18, this->window->getSize().y / 1.8);
  this->texts["COUNTER_AWAITING"] = text;

  GameState::showCardText(activePreset.getCardByIndex(currentCardIndex).getTitle());
}

void GameState::UpdateButtons() {
  static bool flag = 1;

  for (auto &it : this->buttons) {
    it.second->Update(this->MousePosView);
  }

  if (this->buttons["BACK_BTN"]->isPressed() and this->getKeyTime()) {
    flag = 1;
    this->ToQuit = 1;
  }

  // Показать описание // Show description
  if (this->showingTitle and this->buttons["ACTIVE_CARD_BTN"]->isPressed() and this->getKeyTime()) {

    this->showingTitle = 0;
    // DESCRIPTION взять из активной карточки // DESCRIPTION taken from the active card
    GameState::showCardText(activePreset.getCardByIndex(currentCardIndex).getText());
  }
    // Спрятать описание - показать титул // Hide description - show title
  else if (!this->showingTitle and this->buttons["ACTIVE_CARD_BTN"]->isPressed() and this->getKeyTime()) {
    this->showingTitle = 1;
    // title взять из активной карточки // title taken from the active card
    GameState::showCardText(activePreset.getCardByIndex(currentCardIndex).getTitle());
  }

  if (this->buttons["SWIPE_RIGHT_BTN"]->isPressed() and this->getKeyTime()) {
    if (!reverse) {
      if (currentCardIndex < activePreset.getLength()) {
        if (!activePreset.getCardByIndex(currentCardIndex).isFailed()) {
          failedCardsIndexes.push_back(currentCardIndex);
          activePreset.getCardByIndex(currentCardIndex).setFailed(true);
          awaitingCardsIndexes.pop_back();
          currentCardIndex++;
          showCurrentCard();
          if (currentCardIndex == activePreset.getLength() - 1) {
            reverse = true;
          }
        }
      }
    }
  }

  if (this->buttons["SWIPE_LEFT_BTN"]->isPressed() and this->getKeyTime()) {
    if (!reverse) {
      if (currentCardIndex < activePreset.getLength()) {
        if (!activePreset.getCardByIndex(currentCardIndex).isFailed()) {
          activePreset.getCardByIndex(currentCardIndex).setFailed(false);
          awaitingCardsIndexes.pop_back();
          currentCardIndex++;
          showCurrentCard();
          if (currentCardIndex == activePreset.getLength() - 1) {
            reverse = true;
          }
        }
      }
    } else {
        this->buttons["SWIPE_RIGHT_BTN"]->Hide(1);
      if (!failedCardsIndexes.empty()) {
        currentCardIndex = failedCardsIndexes.at(0);
        failedCardsIndexes.erase(failedCardsIndexes.begin());
        activePreset.getCardByIndex(currentCardIndex).setFailed(false);
        showCurrentCard();
      }
    }
  }

}

void GameState::UpdateSprites() {
}

void GameState::UpdateEvents() {
  while (this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) {
      this->window->close();
    }
  }
}

void GameState::UpdateKeyBoardBinds(const float &dt) {
  this->CheckForQuit();
}

//RENDER
void GameState::Render(sf::RenderTarget *target) {
  if (!target) {
    target = this->window;
  }

  target->draw(this->bg);
  this->RenderButtons(target);
  this->RenderSprites(target);
  this->RenderDropDownLists(target);
  this->RenderTextes(target);

}

void GameState::RenderButtons(sf::RenderTarget *target) {
  for (auto &it : this->buttons) {
    it.second->Render(target);
  }
}

void GameState::RenderSprites(sf::RenderTarget *target) {
  for (auto &it : this->sprites) {
    target->draw(it.second);
  }
}

void GameState::RenderDropDownLists(sf::RenderTarget *target) {
  for (auto &it : this->dropDownLists) {
    it.second->Render(target);
  }
}

void GameState::RenderTextes(sf::RenderTarget *target) {
  for (auto &it : this->texts) {
    target->draw(it.second);
  }

  for (auto &it : this->cardText) {
    target->draw(it);
  }
}

void GameState::EndState() {
  std::cout << "ENDING...";
}

void GameState::showCardText(std::string cardTitle) {
  this->cardText.clear();
  sf::Vector2f spriteTopLeft = this->buttons["ACTIVE_CARD_BTN"]->getPos();

  const float maxWidth = this->textures["ACTIVE_CARD"].getSize().x * this->scale;
  unsigned int characterSize = 40 * this->scale;
  auto lines = wordWrap(cardTitle, this->font, characterSize, maxWidth - 15 * this->scale);

  float lineSpacing = 1.1f * 2 * this->scale;
  float yOffset = 10 * this->scale;
  for (const auto &line : lines) {
    sf::Text sfText(line, font, characterSize);
    sfText.setColor(sf::Color::Black);
    sfText.setPosition(spriteTopLeft.x + 10 * this->scale, spriteTopLeft.y + yOffset);
    yOffset += sfText.getLocalBounds().height * lineSpacing;
    this->cardText.push_back(sfText);
  }
}

std::vector<std::string> wordWrap(const std::string &text, sf::Font &font, unsigned int characterSize, float maxWidth) {
  std::vector<std::string> lines;
  std::istringstream wordStream(text);
  std::string word;
  std::string currentLine;

  while (wordStream >> word) {
    std::string testLine = currentLine + (currentLine.empty() ? "" : " ") + word;
    sf::Text testText(testLine, font, characterSize);
    if (testText.getLocalBounds().width > maxWidth) {
      if (!currentLine.empty()) {
        lines.push_back(currentLine);
        currentLine.clear();
      }
      currentLine = word;
    } else {
      currentLine = testLine;
    }
  }

  if (!currentLine.empty()) {
    lines.push_back(currentLine);
  }

  return lines;
}