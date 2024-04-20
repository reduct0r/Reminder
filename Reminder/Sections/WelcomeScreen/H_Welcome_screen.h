// H_Welcome_screen.h
#pragma once

#include <SFML/Window.hpp>
#include "../../UI/UI_anims.h"
#include "../../Init/H_Init.h"
#include "H_settings.h"

namespace Reminder 
{
    class TextureManager;
    class WindowSpecs;
}

void ShowWelcomeScreen();
void DemoCard(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
void ShowUI(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
void ShowMainMenu(sf::RenderWindow& mainWindow);
bool Reminder::JumpAnim(sf::RenderWindow& mainWindow, sf::Sprite& button_log, sf::Sprite& button_reg, sf::Sprite& logo, sf::Sprite& log_field, sf::Sprite& pass_field);
