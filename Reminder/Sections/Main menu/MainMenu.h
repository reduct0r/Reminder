#pragma once
#include "../../Init/H_Init.h"
#include "Settings.h"
#include "MainMenuState.h"

class MainMenu
{
private:
    Settings gfxSettings;

    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    void InitVars();
    void InitWindow();
    void InitStates();
    void InitSettings();

public:
    // Core
    MainMenu();
    virtual ~MainMenu();
    void Run();

    // Update
    void Update();
    void UpdateEvents();
    void UpdateDT();        //  Обновление переменной времени отрисовки кадра

    //Render
    void Render();

    // Functions
    void EndApplication();


};
