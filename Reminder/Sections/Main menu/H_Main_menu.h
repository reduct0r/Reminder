#pragma once
#include "../../Init/H_Init.h"
#include "H_settings.h"
namespace sf 
{
    class RenderWindow;
}

namespace Reminder 
{
    class TextureManager;
    class WindowSpecs;
}

void ShowMainMenu(sf::RenderWindow& mainWindow);
void ShowUI(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
bool ExitShure(sf::RenderWindow& mainWindow);