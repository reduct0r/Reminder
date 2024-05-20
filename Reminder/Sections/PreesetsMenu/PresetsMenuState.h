#pragma once
#include "SettingsState.h"
#include "../../State.h"
#include "../../Game/GameProcess.h"
#include "../../Auth/Database.h"
#include "../../UI/MultilineTextBox.hpp"

class PresetsMenuState :
    public State {
 private:
  Settings &gfxSettings;

  sf::Sprite bg;
  sf::Font font;
  sf::Event sfEvent;
  std::map<std::string, ReminderUI::Button *> buttons;
  std::map<std::string, ReminderUI::DropDownList *> dropDownLists;
  std::map<std::string, ReminderUI::TextBox*> textboxes;
  std::map<std::string, ReminderUI::MultiLineTextBox*> textboxesMulti;
  std::map<std::string, sf::Text> texts;
  std::vector<std::string> presetsName;
  std::vector<Reminder::CardPreset> &userPresets;
  Reminder::CardPreset &activePreset;
  Reminder::Database *database;
  UserDAO &existingUser;
  sf::Clock dtClock;

  float scale = 1;
  bool startFullScreen = 0;
  float dt;

  //Inits
  void InitVars();
  void InitBG();
  void InitFonts();
  void InitButtons();
  void InitTextures();
  void InitSprites();
  void InitTexts();
  void InitDropDownLists();
  void InitTextBoxes();

 public:
  PresetsMenuState(sf::RenderWindow *window,
                   std::stack<State *> *states,
                   Settings &gfxSettings,
                   std::vector<Reminder::CardPreset> &userPresets,
                   Reminder::CardPreset &activePreset,
                   Reminder::Database *database,
                   UserDAO &existingUser);

  virtual ~PresetsMenuState();

  void Update(const float &dt);
  void UpdateDT();
  void UpdateButtons();
  void UpdateSprites();
  void UpdateEvents();
  void UpdateKeyBoardBinds(const float &dt);
  void UpdateDropDownLists(const float &dt);
  void UpdateTextBoxesEvent();

  void RenderTextBoxes(sf::RenderTarget* target = nullptr);
  void RenderButtons(sf::RenderTarget *target = nullptr);
  void RenderSprites(sf::RenderTarget *target = nullptr);
  void RenderDropDownLists(sf::RenderTarget *target = nullptr);
  void RenderTextes(sf::RenderTarget *target = nullptr);
  void Render(sf::RenderTarget *target = nullptr);
  void EndState();
};