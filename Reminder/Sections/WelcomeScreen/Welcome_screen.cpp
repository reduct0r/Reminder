#include "H_Welcome_screen.h"
#include "../../UI Animations/UI_anims.h"

void ShowWelcomeScreen()
{
    Reminder::WindowSpecs mainWindowSpecs;
    sf::RenderWindow mainWindow(sf::VideoMode(mainWindowSpecs.getWidth(), mainWindowSpecs.getHeight()), mainWindowSpecs.getTitle());
    mainWindow.setFramerateLimit(mainWindowSpecs.getFPS());
    Reminder::TextureManager textureManager = Reminder::InitTexturesMain();                      // Загрузка текстур

    //DemoCard(mainWindow, textureManager, mainWindowSpecs);
    ShowUI(mainWindow, textureManager, mainWindowSpecs);
}

// Демонстрационная карточка
void DemoCard(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs)
{
    sf::Sprite sprite(textureManager.getTexture("card1"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);     // Точка поворота в центр спрайта
    sprite.setPosition(mainWindowSpecs.getWidth() / 2, mainWindowSpecs.getHeight() / 2);         // Позиционирование спрайта в центре окна

    float scaleX = 0.5f; // Исходный масштаб по X и Y
    const float scaleY = 0.5f;
    sprite.setScale(scaleX, scaleY);

    // Параметры для анимации сжатия и расширения (поворот)
    bool squeezing = 1; // Направление изменения масштаба
    bool changed = 0;   // Замена текстуры
    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
        }
        if (squeezing)
        {
            scaleX -= 0.01;
        }
        else
        {
            scaleX += 0.01;
        }

        if (scaleX <= 0 or scaleX >= 0.5)         // Изменение направления анимации и текстуры при достижении границ   
        {
            if (scaleX <= 0 and changed == 0)
            {
                sprite.setTexture(textureManager.getTexture("card2"));
                changed = 1;
            }

            else if (scaleX <= 0 and changed == 1)
            {
                sprite.setTexture(textureManager.getTexture("card1"));
                changed = 0;
            }

            squeezing = !squeezing;
        }

        sprite.setScale(scaleX, scaleY);

        mainWindow.clear();
        mainWindow.draw(sprite);
        mainWindow.display();
    }

}

void ShowUI(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs)
{
    sf::Sprite background(textureManager.getTexture("Background_Main"));
    background.setScale(static_cast<float>(mainWindow.getSize().x) / textureManager.getTexture("Background_Main").getSize().x,
        static_cast<float>(mainWindow.getSize().y) / textureManager.getTexture("Background_Main").getSize().y);

    sf::Texture button1T = textureManager.getTexture("Login_button");
    sf::Texture button1hT = textureManager.getTexture("Login_button_hovered");
    sf::Texture button2T = textureManager.getTexture("Reg_button");
    sf::Texture button2hT = textureManager.getTexture("Reg_button_hovered");


    sf::Sprite button1(textureManager.getTexture("Login_button"));
    sf::Sprite button2(textureManager.getTexture("Reg_button"));
    float buttonWidth = button1.getLocalBounds().width;
    float buttonHeight = button1.getLocalBounds().height;

    /* Масштабировние спрайтов в соотвествии с разрешением окна. Сохранение пропорций */
    float scaleX = mainWindow.getSize().x / float(textureManager.getTexture("Background_Main").getSize().x); // масштаб по оси X
    float scaleY = mainWindow.getSize().y / float(textureManager.getTexture("Background_Main").getSize().y); // масштаб по оси Y
    button1.setScale(scaleX, scaleY);
    button2.setScale(scaleX, scaleY);

    // Предварительно устанавливаем позиции кнопок по середине окна c последующим смещением
    float ButttonPosX = mainWindow.getSize().x / 2.0 - button1.getGlobalBounds().width / 2.0;
    float ButttonPosY = mainWindow.getSize().y / 2.0 - button1.getGlobalBounds().height / 2.0;

    // Смещения
    button1.setPosition(ButttonPosX, ButttonPosY + mainWindow.getSize().y / 6.0);
    button2.setPosition(ButttonPosX, ButttonPosY + mainWindow.getSize().y / 30.0);

    sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);
    sf::FloatRect buttonBounds = button1.getGlobalBounds();

    Reminder::ButtonState button1st;
    Reminder::ButtonState button2st;

    while (mainWindow.isOpen())
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);

        Reminder::SmoothButtonAnim(button1, mousePosition, button1T, button1hT, button1st);

        Reminder::SmoothButtonAnim(button2, mousePosition, button2T, button2hT, button2st);


        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
             
            /*...*/

        }

        mainWindow.clear();
        mainWindow.draw(background);
        mainWindow.draw(button1);
        mainWindow.draw(button2);
        mainWindow.display();
    }
}