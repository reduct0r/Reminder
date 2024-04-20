#include "H_Welcome_screen.h"

void ShowWelcomeScreen()
{
    Reminder::WindowSpecs mainWindowSpecs;
    sf::RenderWindow mainWindow(sf::VideoMode(mainWindowSpecs.getWidth(), mainWindowSpecs.getHeight()), mainWindowSpecs.getTitle());
    mainWindow.setFramerateLimit(mainWindowSpecs.getFPS());
    Reminder::TextureManager textureManager = Reminder::InitTexturesWelcome();                      // Загрузка текстур

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

    sf::Sprite button_log(button1T);
    sf::Sprite button_reg(button2T);
    sf::Sprite logo(textureManager.getTexture("logo"));
    sf::Sprite log_field(textureManager.getTexture("login_field"));
    sf::Sprite pass_field(textureManager.getTexture("passw_field"));
    sf::Sprite github(textureManager.getTexture("Github_icon"));
    sf::Sprite back(textureManager.getTexture("back"));

    float buttonWidth = button_log.getLocalBounds().width;
    float buttonHeight = button_log.getLocalBounds().height;

    /* Масштабировние спрайтов в соотвествии с разрешением окна. Сохранение пропорций */
    float scaleX = mainWindow.getSize().x / float(textureManager.getTexture("Background_Main").getSize().x); // масштаб по оси X
    float scaleY = mainWindow.getSize().y / float(textureManager.getTexture("Background_Main").getSize().y); // масштаб по оси Y
    button_log.setScale(scaleX, scaleY);
    button_reg.setScale(scaleX, scaleY);
    logo.setScale(scaleX, scaleY);
    github.setScale(scaleX, scaleY);
    back.setScale(scaleX / 10.0, scaleY / 10.0);
    // Предварительно устанавливаем позиции по середине окна c последующим смещением
    float ButttonPosX = mainWindow.getSize().x / 2.0 - button_log.getGlobalBounds().width / 2.0;
    float ButttonPosY = mainWindow.getSize().y / 2.0 - button_log.getGlobalBounds().height / 2.0;

    float LogoPosX = mainWindow.getSize().x / 2.0 - logo.getGlobalBounds().width / 2.0;
    float LogoPosY = mainWindow.getSize().y / 2.0 - logo.getGlobalBounds().height / 2.0;

    /* ======== ПОЛЯ ======== */
    log_field.setColor(sf::Color(255, 255, 255, 0));
    pass_field.setColor(sf::Color(255, 255, 255, 0));
    float FieldPosX = mainWindow.getSize().x / 2.0 - log_field.getGlobalBounds().width / 2.0;
    float FieldPosY = mainWindow.getSize().y / 2.0 - log_field.getGlobalBounds().height / 2.0;
    log_field.setScale(mainWindow.getSize().x / 1900.0, mainWindow.getSize().x / 1900.0);
    pass_field.setScale(log_field.getScale());
    log_field.setPosition(ButttonPosX, ButttonPosY - mainWindow.getSize().y / 15.0);
    pass_field.setPosition(ButttonPosX, log_field.getPosition().y + mainWindow.getSize().y / 8.5);

    // Смещения
    button_log.setPosition(ButttonPosX, ButttonPosY + mainWindow.getSize().y / 6.0);
    button_reg.setPosition(ButttonPosX, ButttonPosY + mainWindow.getSize().y / 30.0);
    logo.setPosition(LogoPosX + mainWindow.getSize().x / 150.0, LogoPosY - mainWindow.getSize().y / 6.0);
    github.setPosition(mainWindow.getSize().x / 100.0, mainWindow.getSize().y * 0.9);
    back.setPosition(mainWindow.getSize().x / 100.0, mainWindow.getSize().x / 100.0);

    sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);
    sf::FloatRect buttonBounds = button_log.getGlobalBounds();

    Reminder::ButtonState button1st;
    Reminder::ButtonState button2st;

    UI::TextBox Login_textBox;
    Login_textBox.setSize(mainWindow.getSize().y / 2.1, mainWindow.getSize().x / 40.0);
    Login_textBox.setPosition(ButttonPosX + mainWindow.getSize().x / 20.0, ButttonPosY - mainWindow.getSize().y / 23.0);
    Login_textBox.setBorder(0);
    
    UI::TextBox Password_textBox;
    Password_textBox.setSize(mainWindow.getSize().y / 2.1, mainWindow.getSize().x / 40.0);
    Password_textBox.setPosition(ButttonPosX + mainWindow.getSize().x / 20.0, ButttonPosY + mainWindow.getSize().y / 13.0);;
    Password_textBox.setBorder(0);

    sf::String Login;
    sf::String Password;

    bool reg = 0;

    while (mainWindow.isOpen())
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);

        Reminder::SmoothButtonAnim(button_log, mousePosition, button1T, button1hT, button1st);

        Reminder::SmoothButtonAnim(button_reg, mousePosition, button2T, button2hT, button2st);

        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            Login_textBox.handleEvent(event);
            Password_textBox.handleEvent(event);

            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    // Проверка, было ли нажатие внутри кнопки регистрации
                    if (button_reg.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) and reg == 0) 
                    {
                        reg = 1;
                    }
                    // Получение логина и пароля по нажатию кнопки регистрации после ввода текста в поля
                    else if (button_reg.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) and reg == 1 and Login_textBox.getCurrentText() != "" and Password_textBox.getCurrentText() != "")
                    {
                        Login = Login_textBox.getCurrentText();
                        Password = Password_textBox.getCurrentText();
                        
                        std::string L = Login;
                        std::string P = Password;
                        std::cout << L << " " << P << "\n";
                        reg = 0;

                        /* ЗАРЕГИСТРИРОВАТЬ ПОЛЬЗОВАТЕЛЯ, ПЕРЕХОД В ГЛАВНОЕ МЕНЮ */

                        ShowMainMenu(mainWindow);
                        return;
                    }

                    else if (github.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        std::string url = "https://github.com/reduct0r/Reminder";

                        #ifdef _WIN32
                            std::string command = "start " + url + ""; // Для Windows
                        #elif __APPLE__
                            std::string command = "open " + url + ""; // Для macOS
                        #endif

                        // Вызываем командную строку сформированной команды
                        system(command.c_str());
                    }

                    else if (back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) // Перезапустить вкладку
                    {
                        ShowUI(mainWindow, textureManager, mainWindowSpecs);
                        return;
                    }

                    // Проверка, было ли нажатие внутри кнопки входа
                    else if (button_log.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) and reg == 0)
                    {
                        /* ПРОЦЕСС ВХОДА, ЗАТЕМ ГЛАВНОЕ МЕНЮ*/

                        ShowMainMenu(mainWindow);
                        return;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape and reg == 1) // Перезапустить вкладку
            {
                ShowUI(mainWindow, textureManager, mainWindowSpecs);
                return;
            }

        }
        mainWindow.clear();

        mainWindow.draw(background);
        mainWindow.draw(button_log);
        mainWindow.draw(button_reg);
        mainWindow.draw(logo);
        mainWindow.draw(log_field);
        mainWindow.draw(pass_field);
        mainWindow.draw(github);

        if (reg) // Процесс регистрации
        {
            if (Reminder::ShowRegisterField(mainWindow, button_log, button_reg, logo, log_field, pass_field, reg))
            {
                Login_textBox.draw(mainWindow);
                Password_textBox.draw(mainWindow);
            }
            mainWindow.draw(back);
        }

        mainWindow.display();
    }
}