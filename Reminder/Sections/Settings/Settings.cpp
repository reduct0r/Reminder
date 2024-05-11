#include "Settings.h"


Settings::Settings()
{
    this->title = "DEFAULT";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = 0;
    this->VSync = 0;
    this->frameLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

void Settings::SaveToFile(const std::string path)
{
    std::ofstream ofs(path);
    if (ofs.is_open())
    {
        ofs << this->title << "\n";
        ofs << this->resolution.width << " " << this->resolution.height << "\n";
        ofs << this->fullscreen << "\n";
        ofs << this->frameLimit << "\n";
        ofs << this->VSync << "\n";
        ofs << this->contextSettings.antialiasingLevel << "\n";
        ofs << this->sound;
    }
    ofs.close();
}

void Settings::LoadFromFile(const std::string path)
{
    std::ifstream ifs(path);
    if (ifs.is_open())
    {
        std::getline(ifs, this->title);
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> this->fullscreen;
        ifs >> this->frameLimit;
        ifs >> this->VSync;
        ifs >> this->contextSettings.antialiasingLevel;\
        ifs >> this->sound;
    }
    ifs.close();
}