#pragma once
#include "WelcomeScreenState.h"

class WelcomeScreen
{
private:

    class Settings
    {
    public:

        std::string title;
        sf::VideoMode resolution;
        bool fullscreen;
        bool VSync;
        unsigned frameLimit;
        sf::ContextSettings contextSettings;
        std::vector<sf::VideoMode> videoModes;

        Settings()
        {
            this->title = "DEFAULT";
            this->resolution = sf::VideoMode::getDesktopMode();
            this->fullscreen = 0;
            this->VSync = 0;
            this->frameLimit = 120;
            this->contextSettings.antialiasingLevel = 0;
            this->videoModes = sf::VideoMode::getFullscreenModes();
        }

        void SaveToFile(const std::string path)
        {
            std::ofstream ofs(path);
            if (ofs.is_open())
            {
                ofs << this->title;
                ofs << this->resolution.width << " " << this->resolution.height;
                ofs << this->fullscreen;
                ofs << this->frameLimit;
                ofs << this->VSync;
                ofs << this->contextSettings.antialiasingLevel;
            }
            ofs.close();
        }

        void LoadFromFile(const std::string path)
        {
            std::ifstream ifs(path);
            if (ifs.is_open())
            {
                std::getline(ifs, this->title);
                ifs >> this->resolution.width >> this->resolution.height;
                ifs >> this->fullscreen;
                ifs >> this->frameLimit;
                ifs >> this->VSync;
                ifs >> this->contextSettings.antialiasingLevel;
            }
            ifs.close();
        }
    };

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
