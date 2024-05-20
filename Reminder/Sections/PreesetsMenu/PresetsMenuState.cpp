#include "PresetsMenuState.h"
#include <iostream>
#include "../WelcomeScreen/WelcomeScreen.h"

PresetsMenuState::PresetsMenuState(sf::RenderWindow *window,
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
  this->InitTextBoxes();

  this->startFullScreen = this->gfxSettings.fullscreen;
}

PresetsMenuState::~PresetsMenuState() {
  auto it = this->buttons.begin();
  for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }

  delete database;
}

// INIT
void PresetsMenuState::InitVars() {
  this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_PRESETS"].getSize().x;
  presetsName.clear();
  if (!userPresets.empty()) {
    presetsName.push_back("Choose Preset");
    for (auto &preset : userPresets) {
      presetsName.push_back(preset.getName());
    }
  } else {
    this->presetsName = {"No presets"};
  }
}

void PresetsMenuState::InitBG() {
  float scale = this->scale;

  this->bg.setScale(sf::Vector2f(scale, scale));
  this->bg.setTexture(this->textures["BG_PRESETS"]);

}

void PresetsMenuState::InitFonts() {
  if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf")) {
    throw ("PresetsState: COULD NOT LOAD FONT");
  }
}

void PresetsMenuState::InitButtons() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);

  float scale = this->scale;
  this->buttons["BACK_BTN"] = new ReminderUI::Button(winY / 18,
                                                     winY / 18,
                                                     scale,
                                                     this->textures["BACK"],
                                                     this->textures["BACK"],
                                                     this->textures["BACK"]);

  this->buttons["MY_PRESETS_BTN"] =
      new ReminderUI::Button(0,
                             40,
                             winX / 3.2 - this->textures["MY_PRESETS"].getSize().x * this->scale / 2,
                             winY / 2 - this->textures["MY_PRESETS"].getSize().y * this->scale / 2,
                             scale,
                             scale,
                             &this->font,
                             "",
                             this->textures["MY_PRESETS"],
                             this->textures["MY_PRESETS"],
                             this->textures["MY_PRESETS"]);

  this->buttons["NEW_PRESET_BTN"] =
      new ReminderUI::Button(0,
                             40,
                             winX / 1.5 - this->textures["NEW_PRESET"].getSize().x * this->scale / 2,
                             winY / 2 - this->textures["NEW_PRESET"].getSize().y * this->scale / 2,
                             scale,
                             scale,
                             &this->font,
                             "",
                             this->textures["NEW_PRESET"],
                             this->textures["NEW_PRESET"],
                             this->textures["NEW_PRESET"]);

  this->buttons["DELETE_BTN"] =
      new ReminderUI::Button(winX / 1.15 - this->textures["DELETE_1"].getSize().x * this->scale / 2,
                             winY / 1.2,
                             scale,
                             this->textures["DELETE_1"],
                             this->textures["DELETE_2"],
                             this->textures["DELETE_2"]);
  this->buttons["DELETE_BTN"]->Hide(1);

  this->buttons["PREVIEW_BTN"] =
      new ReminderUI::Button(winX / 1.15 - this->textures["PREVIEW_1"].getSize().x * this->scale / 2,
                             winY / 1.38,
                             scale,
                             this->textures["PREVIEW_1"],
                             this->textures["PREVIEW_2"],
                             this->textures["PREVIEW_2"]);
  this->buttons["PREVIEW_BTN"]->Hide(1);

  this->buttons["IMPORT_BTN"] =
      new ReminderUI::Button(winX / 1.15 - this->textures["IMPORT_1"].getSize().x * this->scale / 2,
                             winY / 2.5,
                             scale,
                             this->textures["IMPORT_1"],
                             this->textures["IMPORT_2"],
                             this->textures["IMPORT_2"]);
  this->buttons["IMPORT_BTN"]->Hide(1);

  this->buttons["SAVE_BTN"] =
      new ReminderUI::Button(winX / 1.15 - this->textures["SAVE_1"].getSize().x * this->scale / 2,
                             winY / 1.96,
                             scale,
                             this->textures["SAVE_1"],
                             this->textures["SAVE_2"],
                             this->textures["SAVE_2"]);
  this->buttons["SAVE_BTN"]->Hide(1);

  this->buttons["CHOOSE_BTN"] =
      new ReminderUI::Button(winX / 28, winY / 1.38,
                             scale,
                             this->textures["USE_THIS_1"],
                             this->textures["USE_THIS_2"],
                             this->textures["USE_THIS_2"]);
  this->buttons["CHOOSE_BTN"]->Hide(1);

  this->buttons["NEXT_BTN"] =
      new ReminderUI::Button(winX / 1.3, winY / 1.2,
                             scale,
                             this->textures["NEXT_1"],
                             this->textures["NEXT_2"],
                             this->textures["NEXT_2"]);
  this->buttons["NEXT_BTN"]->Hide(1);

  this->buttons["CLEAR_BTN"] =
      new ReminderUI::Button(winX / 1.3, winY / 1.8,
                             scale,
                             this->textures["CLEAR_1"],
                             this->textures["CLEAR_2"],
                             this->textures["CLEAR_2"]);
  this->buttons["CLEAR_BTN"]->Hide(1);

  this->buttons["FINISH_BTN"] =
      new ReminderUI::Button(winX / 1.4, winY / 2.3,
                             scale,
                             this->textures["FINISH_1"],
                             this->textures["FINISH_2"],
                             this->textures["FINISH_2"]);
  this->buttons["FINISH_BTN"]->Hide(1);
}

void PresetsMenuState::InitTextures() {
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

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/DELETE.png");
  this->textures["DELETE_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/DELETE2.png");
  this->textures["DELETE_2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/PREVIEW.png");
  this->textures["PREVIEW_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/PREVIEW2.png");
  this->textures["PREVIEW_2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/IMPORT.png");
  this->textures["IMPORT_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/IMPORT2.png");
  this->textures["IMPORT_2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/SAVE.png");
  this->textures["SAVE_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/SAVE2.png");
  this->textures["SAVE_2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/USE_THIS.png");
  this->textures["USE_THIS_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/USE_THIS2.png");
  this->textures["USE_THIS_2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/group 62.png");
  this->textures["PRESET_FIELDS"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/NEXT.png");
  this->textures["NEXT_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/NEXT2.png");
  this->textures["NEXT_2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/CLEAR.png");
  this->textures["CLEAR_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/CLEAR2.png");
  this->textures["CLEAR_2"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/FINISH.png");
  this->textures["FINISH_1"] = texture;

  texture.loadFromFile("Resources/Textures/UI/PresetsMenu/FINISH2.png");
  this->textures["FINISH_2"] = texture;
}

void PresetsMenuState::InitSprites() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);
  float scale = this->scale;

  sf::Sprite sprite;
  sprite.setScale(scale, scale);
  sprite.setTexture(this->textures["LOGO"]);
  sprite.setPosition(winX / 2.0 - this->textures["LOGO"].getSize().x * scale / 2.05,
                     winY / 3 - this->textures["LOGO"].getSize().y * scale / 2.0 - winY / 7.0);
  this->sprites["LOGO"] = sprite;

  sf::Sprite sprite1;
  sprite1.setTexture(this->textures["PRESET_FIELDS"]);
  sprite1.setPosition(winX / 30, winY / 100);
  sprite1.setScale(0, 0);
  this->sprites["PRESET_FIELDS_SPRITE"] = sprite1;

}

void PresetsMenuState::InitDropDownLists() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);
  float scale = this->scale;

  this->dropDownLists["PRESETS_LIST"] = new ReminderUI::DropDownList(this->scale * 0.9,
                                                                     0,
                                                                     winX / 2 - this->textures["DDL_SECOND"].getSize().x
                                                                         * scale / 2 * 0.9,
                                                                     winY / 4 - this->textures["DDL_SECOND"].getSize().y
                                                                         * scale / 2 * 0.9,
                                                                     &this->font,
                                                                     50,
                                                                     this->presetsName,
                                                                     this->textures["DDL_SECOND"],
                                                                     this->textures["DDL_SECOND_HOVER"],
                                                                     this->textures["DDL_SECOND"]);
//  if (!this->activePreset.getName().empty()) {
//    this->dropDownLists["PRESETS_LIST"]->setActiveEl(this->activePreset.getNumber() - 1);
//  }
  this->dropDownLists["PRESETS_LIST"]->Hide(1);
}

void PresetsMenuState::InitTextBoxes() {
  //first two parameter for size, second two for position and the last one for thickness.
  this->textboxes["PRESET_NAME"] = new ReminderUI::TextBox(0, 0, 0, 0, 0);
  this->textboxes["PRESET_NAME"]->SetColor(sf::Color::White);

  this->textboxes["CARD_NAME"] = new ReminderUI::TextBox(0, 0, 0, 0, 0);
  this->textboxes["CARD_NAME"]->SetColor(sf::Color::White);

  this->textboxesMulti["DESCRIPTION"] = new ReminderUI::MultiLineTextBox(0, 0, 0, 0, this->font, 40 * this->scale);
}

void PresetsMenuState::InitTexts() {
  sf::Text text;
  text.setFont(this->font);
  text.setFillColor(sf::Color::Black);
  text.setCharacterSize(this->scale * 40);
  text.setPosition(this->window->getSize().x / 2.57, this->window->getSize().y / 2.63);
  text.setString(std::to_string(this->presetsName.size() - 1));
  this->texts["COUNTER_TXT"] = text;
}

// UPDATE
void PresetsMenuState::Update(const float &dt) {
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

void PresetsMenuState::UpdateDropDownLists(const float &dt) {
  for (auto &it : this->dropDownLists) {
    it.second->Update(this->MousePosView, dt);
  }
}

void PresetsMenuState::UpdateTextBoxesEvent() {
  for (auto &it : this->textboxes) {
    it.second->handleEvent(this->sfEvent);
  }

  for (auto &it : this->textboxesMulti) {
    it.second->handleEvent(this->sfEvent);
  }
}

void PresetsMenuState::UpdateButtons() {
  static bool flag = 1;

  for (auto &it : this->buttons) {
    it.second->Update(this->MousePosView);
  }

  if (this->buttons["BACK_BTN"]->isPressed() and this->getKeyTime()) {
    flag = 1;
    this->ToQuit = 1;
  }

  // Мои пресеты
  if (flag and this->buttons["MY_PRESETS_BTN"]->isPressed() and this->getKeyTime()) {
    flag = 0;
    this->buttons["MY_PRESETS_BTN"]->setPos(
        this->window->getSize().x / 6.0 - this->textures["MY_PRESETS"].getSize().x * this->scale / 2.0,
        this->buttons["MY_PRESETS_BTN"]->getPos().y);
    this->buttons["NEW_PRESET_BTN"]->Hide(1);
    this->buttons["MY_PRESETS_BTN"]->setText("\n\nClick to return");
    this->dropDownLists["PRESETS_LIST"]->Hide(0);

    this->texts["COUNTER_TXT"].move(-this->scale * 280, 0);

    this->buttons["DELETE_BTN"]->Hide(0);
    this->buttons["PREVIEW_BTN"]->Hide(0);
    this->buttons["IMPORT_BTN"]->Hide(0);
    this->buttons["SAVE_BTN"]->Hide(0);
    this->buttons["CHOOSE_BTN"]->Hide(0);
  } else if (!flag and this->buttons["MY_PRESETS_BTN"]->isPressed() and this->getKeyTime()) {
    flag = 1;
    this->buttons["MY_PRESETS_BTN"]->setPos(
        this->window->getSize().x / 3.2 - this->textures["MY_PRESETS"].getSize().x * this->scale / 2,
        this->window->getSize().y / 2 - this->textures["MY_PRESETS"].getSize().y * this->scale / 2);
    this->buttons["NEW_PRESET_BTN"]->Hide(0);
    this->buttons["MY_PRESETS_BTN"]->setText("");

    this->InitDropDownLists();
    this->dropDownLists["PRESETS_LIST"]->Hide(1);

    this->texts["COUNTER_TXT"].move(this->scale * 280, 0);

    this->buttons["DELETE_BTN"]->Hide(1);
    this->buttons["PREVIEW_BTN"]->Hide(1);
    this->buttons["IMPORT_BTN"]->Hide(1);
    this->buttons["SAVE_BTN"]->Hide(1);
    this->buttons["CHOOSE_BTN"]->Hide(1);
  }

  // Новый пресет
  if (flag and this->buttons["NEW_PRESET_BTN"]->isPressed() and this->getKeyTime()) {
    InitVars();
    InitTexts();
    InitDropDownLists();
    flag = 0;
    this->buttons["NEW_PRESET_BTN"]->setPos(
        this->window->getSize().x / 1.2 - this->textures["NEW_PRESET"].getSize().x * this->scale / 2.0,
        this->window->getSize().y / 10);
    this->texts["COUNTER_TXT"].setCharacterSize(0);
    this->buttons["MY_PRESETS_BTN"]->Hide(1);
    this->buttons["NEW_PRESET_BTN"]->setText("\n\n\n\n\n  Click to return  \nWITHOUT saving");
    this->sprites["LOGO"].setScale(0, 0);
    this->buttons["BACK_BTN"]->Hide(1);
    this->sprites["PRESET_FIELDS_SPRITE"].setScale(scale, scale);
    this->buttons["FINISH_BTN"]->Hide(0);
    this->buttons["NEXT_BTN"]->Hide(0);
    this->buttons["CLEAR_BTN"]->Hide(0);

    this->textboxes["PRESET_NAME"]->setPosition(this->window->getSize().x / 11.1, this->window->getSize().y / 8.0);
    this->textboxes["PRESET_NAME"]->setSize(this->window->getSize().y / 1.3, this->window->getSize().x / 38.0);

    this->textboxes["CARD_NAME"]->setPosition(this->window->getSize().x / 9.0, this->window->getSize().y / 2.55);
    this->textboxes["CARD_NAME"]->setSize(this->window->getSize().y / 1.45, this->window->getSize().x / 38.0);

    this->textboxesMulti["DESCRIPTION"]->setPos(this->window->getSize().x / 9.0, this->window->getSize().y / 1.95);
    this->textboxesMulti["DESCRIPTION"]->setSize(750 * this->scale, 300 * this->scale);

  } else if (!flag and this->buttons["NEW_PRESET_BTN"]->isPressed() and this->getKeyTime()) {
    InitVars();
    InitTexts();
    InitDropDownLists();
    flag = 1;
    this->buttons["NEW_PRESET_BTN"]->setPos(
        this->window->getSize().x / 1.5 - this->textures["NEW_PRESET"].getSize().x * this->scale / 2,
        this->window->getSize().y / 2 - this->textures["NEW_PRESET"].getSize().y * this->scale / 2);
    this->texts["COUNTER_TXT"].setCharacterSize(this->scale * 40);
    this->buttons["MY_PRESETS_BTN"]->Hide(0);
    this->buttons["NEW_PRESET_BTN"]->setText("");
    this->sprites["LOGO"].setScale(scale, scale);
    this->buttons["BACK_BTN"]->Hide(0);
    this->sprites["PRESET_FIELDS_SPRITE"].setScale(0, 0);
    this->buttons["FINISH_BTN"]->Hide(1);
    this->buttons["NEXT_BTN"]->Hide(1);
    this->buttons["CLEAR_BTN"]->Hide(1);

    this->textboxes["CARD_NAME"]->ClearInput();
    this->textboxes["PRESET_NAME"]->ClearInput();

    this->textboxes["CARD_NAME"]->setSize(0, 0);
    this->textboxes["PRESET_NAME"]->setSize(0, 0);

    this->textboxesMulti["DESCRIPTION"]->clearInput();
    this->textboxesMulti["DESCRIPTION"]->setSize(0, 0);

  }

  if (this->buttons["DELETE_BTN"]->isPressed() and this->getKeyTime()) {
    int indexToRemove = this->dropDownLists["PRESETS_LIST"]->getActiveElementId();
    if (indexToRemove > 0 and indexToRemove < this->presetsName.size()) {
      database->deleteUserPreset(userPresets.at(indexToRemove - 1).getName(), existingUser);
      if (userPresets.at(indexToRemove - 1).getName() == activePreset.getName()) {
        activePreset.setName("");
      }
      this->presetsName.erase(this->presetsName.begin() + indexToRemove);
      userPresets.erase(userPresets.begin() + indexToRemove - 1);
    }

    this->InitDropDownLists();
    this->InitTexts();
    this->texts["COUNTER_TXT"].move(-this->scale * 280, 0);
    this->dropDownLists["PRESETS_LIST"]->Hide(0);
  }

  if (this->buttons["CHOOSE_BTN"]->isPressed() and this->getKeyTime()) {
    int indexToRemove = this->dropDownLists["PRESETS_LIST"]->getActiveElementId();

    if (indexToRemove > 0) {
      activePreset = userPresets.at(this->dropDownLists["PRESETS_LIST"]->getActiveElementId() - 1);
    } else if (this->activePreset.getName().empty()) {
      this->dropDownLists["PRESETS_LIST"]->Blink();
    }
  }

  if (this->buttons["CLEAR_BTN"]->isPressed() and this->getKeyTime()) {
    this->textboxes["CARD_NAME"]->ClearInput();
    this->textboxesMulti["DESCRIPTION"]->clearInput();
    // ОЧИСТИТЬ
  }

  if (this->buttons["NEXT_BTN"]->isPressed() and this->getKeyTime()) {
    std::string description = this->textboxesMulti["DESCRIPTION"]->getInput();
    description.erase(std::remove(description.begin(), description.end(), '\n'), description.end());
    Reminder::Card newCard(this->textboxes["CARD_NAME"]->getCurrentText(), description);
    presetToAdd.addCard(newCard);
    this->textboxes["CARD_NAME"]->ClearInput();
    this->textboxesMulti["DESCRIPTION"]->clearInput();
    //NEXT/
    //ПРОВЕРКА НА ПУСТЫЕ ПОЛЯ
  }

  if (this->buttons["FINISH_BTN"]->isPressed() and this->getKeyTime()) {
    presetToAdd.setName(this->textboxes["PRESET_NAME"]->getCurrentText());
    database->addUserPreset(presetToAdd, existingUser);
    userPresets.push_back(presetToAdd);
    //FINISH - ADD PRESET TO DATABS
    // ПРОВЕРКА НА ПУСТЫЕ ПОЛЯ
  }
}

void PresetsMenuState::UpdateSprites() {
}

void PresetsMenuState::UpdateEvents() {
  while (this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) {
      this->window->close();
    }
    UpdateTextBoxesEvent();
  }
}

void PresetsMenuState::UpdateKeyBoardBinds(const float &dt) {
  this->CheckForQuit();
}

//RENDER
void PresetsMenuState::Render(sf::RenderTarget *target) {
  if (!target) {
    target = this->window;
  }

  target->draw(this->bg);
  this->RenderButtons(target);
  this->RenderSprites(target);
  this->RenderDropDownLists(target);
  this->RenderTextes(target);
  this->RenderTextBoxes(target);

}

void PresetsMenuState::RenderTextBoxes(sf::RenderTarget *target) {
  for (auto &it : this->textboxes) {
    it.second->Render(target);
  }

  for (auto &it : this->textboxesMulti) {
    it.second->draw(target);
  }
}

void PresetsMenuState::RenderButtons(sf::RenderTarget *target) {
  for (auto &it : this->buttons) {
    it.second->Render(target);
  }
}

void PresetsMenuState::RenderSprites(sf::RenderTarget *target) {
  for (auto &it : this->sprites) {
    target->draw(it.second);
  }
}

void PresetsMenuState::RenderDropDownLists(sf::RenderTarget *target) {
  for (auto &it : this->dropDownLists) {
    it.second->Render(target);
  }
}

void PresetsMenuState::RenderTextes(sf::RenderTarget *target) {
  for (auto &it : this->texts) {
    target->draw(it.second);
  }
}

void PresetsMenuState::EndState() {
  std::cout << "ENDING...";
}

