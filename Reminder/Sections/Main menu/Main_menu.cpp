#include "H_Main_menu.h"
#include "../../Init/H_Init.h"

void ShowMainMenu(sf::RenderWindow& mainWindow)
{
    Reminder::TextureManager textureManager = Reminder::InitTexturesMain();                      // Загрузка текстур
    sf::Sprite background(textureManager.getTexture("Background_Main"));
    background.setScale(static_cast<float>(mainWindow.getSize().x) / textureManager.getTexture("Background_Main").getSize().x,
        static_cast<float>(mainWindow.getSize().y) / textureManager.getTexture("Background_Main").getSize().y);


    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                   
                }
            }

            if (event.mouseButton.button == sf::Keyboard::Escape) // Перезапустить вкладку
            {
                ShowMainMenu(mainWindow);
                return;
            }

        }
        mainWindow.clear();

        mainWindow.draw(background);

        mainWindow.display();
    }
}
