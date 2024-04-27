﻿// H_Welcome_screen.h
#pragma once
#include "WelcomeScreenState.h"

namespace sf
{
    class RenderWindow;
}

namespace Reminder
{
    class TextureManager;
    class WindowSpecs;
}

// CLASS
class WelcomeScreen
{
private:
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    sf::ContextSettings windowSettings;
    float dt;
    bool fullsceen;

    std::stack<State*> states;
    std::vector<sf::VideoMode> videoModes;

    // Init
    void InitVars();
    void InitWindow();
    void InitStates();
    
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