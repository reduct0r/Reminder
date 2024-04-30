#pragma once
#include "WelcomeScreenState.h"

class WelcomeScreen
{
private:
    Settings gfxSettings;

    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    // Init
    void InitVars();
    void InitWindow();
    void InitStates();
    void InitSettings();
    
public:
    // Core
    WelcomeScreen();
    virtual ~WelcomeScreen();
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


//void ShowWelcomeScreen();
//void DemoCard(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
//void ShowUI(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
//void ShowMainMenu(sf::RenderWindow& mainWindow);
//bool Reminder::JumpAnim(sf::RenderWindow& mainWindow, sf::Sprite& button_log, sf::Sprite& button_reg, sf::Sprite& logo, sf::Sprite& log_field, sf::Sprite& pass_field);
