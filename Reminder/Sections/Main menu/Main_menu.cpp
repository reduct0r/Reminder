#include "H_Main_menu.h"

bool ExitShure(sf::RenderWindow& mainWindow)
{
    // Показать диалоговое окно перед выходом из аккаунта
    sf::RenderWindow confirmWindow(sf::VideoMode(300, 150), "Exit confirmation");

    // Создание текста с вопросом
    sf::Font font;
    font.loadFromFile("Resources/Fonts/BRLNSR.ttf");
    sf::Text question("Are you sure you want to log out?", font, 20);
    question.setPosition(10, 20);

    // Создание кнопки для подтверждения
    sf::RectangleShape confirmButton(sf::Vector2f(100, 50));
    confirmButton.setPosition(50, 80);
    confirmButton.setFillColor(sf::Color::Green);
    sf::Text confirmText("Yes", font, 20);
    confirmText.setPosition(75, 90);

    // Создание кнопки для отмены
    sf::RectangleShape cancelButton(sf::Vector2f(100, 50));
    cancelButton.setPosition(150, 80);
    cancelButton.setFillColor(sf::Color::Red);
    sf::Text cancelText("No", font, 20);
    cancelText.setPosition(175, 90);

    while (confirmWindow.isOpen())
    {
        sf::Event event;
        while (confirmWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                confirmWindow.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (confirmButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    confirmWindow.close();
                    Reminder::WindowSpecs mainWindowSpecsW;
                    Reminder::TextureManager textureManagerW = Reminder::InitTexturesWelcome();
                    ShowUI(mainWindow, textureManagerW, mainWindowSpecsW);
                    return 0;
                }
                else if (cancelButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    confirmWindow.close();
                    return 1;
                }
            }
        }

        confirmWindow.clear();
        confirmWindow.draw(question);
        confirmWindow.draw(confirmButton);
        confirmWindow.draw(cancelButton);
        confirmWindow.draw(confirmText);
        confirmWindow.draw(cancelText);
        confirmWindow.display();
    }
}

void ShowMainMenu(sf::RenderWindow& mainWindow)
{
    Reminder::TextureManager textureManager = Reminder::InitTexturesMain();                      // Загрузка текстур
    sf::Sprite background(textureManager.getTexture("Background_Main"));
    background.setScale(static_cast<float>(mainWindow.getSize().x) / textureManager.getTexture("Background_Main").getSize().x,
        static_cast<float>(mainWindow.getSize().y) / textureManager.getTexture("Background_Main").getSize().y);

    sf::Sprite logOut(textureManager.getTexture("LogOut"));
    float scaleX = mainWindow.getSize().x / float(textureManager.getTexture("Background_Main").getSize().x); // масштаб по оси X
    float scaleY = mainWindow.getSize().y / float(textureManager.getTexture("Background_Main").getSize().y); // масштаб по оси Y
    logOut.setScale(scaleX / 15.0, scaleY / 15.0);

    // Предварительно устанавливаем позиции по середине окна c последующим смещением
    float PosX = mainWindow.getSize().x / 2.0;
    float PosY = mainWindow.getSize().y / 2.0;

    logOut.setPosition(mainWindow.getSize().x / 100.0, mainWindow.getSize().x / 100.0);

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
                    // Проверка, было ли нажатие внутри кнопки Разлогиниться
                    if (logOut.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        ExitShure(mainWindow);

                        /* РАЗЛОГИНИТЬ */
                    }
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
        mainWindow.draw(logOut);

        mainWindow.display();
    }
}
