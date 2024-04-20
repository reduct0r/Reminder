
#include "H_settings.h"
#include "../Main menu/H_Main_menu.h"
#include "../../Init/H_Init.h"
#include "../../UI/UI_anims.h"
#include <SFML/Window.hpp>


void ShowWelcomeScreen();
void DemoCard(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
void ShowUI(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs);
