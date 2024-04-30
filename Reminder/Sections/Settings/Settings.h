#pragma once
#include "../../State.h"

class Settings
{
public:

    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool VSync;
    bool sound = 1;
    unsigned frameLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;
    

    Settings();

    void SaveToFile(const std::string path);
    void LoadFromFile(const std::string path);

};