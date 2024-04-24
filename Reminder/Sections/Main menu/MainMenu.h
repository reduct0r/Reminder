#pragma once
#include "../../Init/H_Init.h"
#include "H_settings.h"
#include "MainMenuState.h"

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
class MainMenu
{
private:
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    void InitWindow();
    void InitStates();


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



void ShowMainMenu(sf::RenderWindow& mainWindow);
void ShowUI(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
bool ExitShure(sf::RenderWindow& mainWindow);