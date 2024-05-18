#pragma once
#include "Settings.h"
#include "PresetsMenuState.h"

class PresetsMenu {
 private:
  Settings gfxSettings;

  sf::RenderWindow *window;
  sf::Event sfEvent;
  sf::Clock dtClock;
  float dt;

  std::stack<State *> states;

  void InitVars();
  void InitWindow();
  void InitStates();
  void InitSettings();

 public:
  // Core
  PresetsMenu();
  virtual ~PresetsMenu();
  void Run();

  // Update
  void Update();
  void UpdateEvents();
  void UpdateDT();        //  ���������� ���������� ������� ��������� �����

  //Render
  void Render();

  // Functions
  void EndApplication();

};
