#include "UI_anims.h"
#include <iostream>


void Reminder::SmoothButtonAnim(sf::Sprite& button, sf::Vector2i& mousePosition, sf::Texture& buttonT, sf::Texture& button_hT, ButtonState& button_st)
{
    float speed = 8.5;

    if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
    {
        if (button_st.alpha > 0 and !button_st.changedButton)
        {
            button_st.alpha -= speed; // Изменение затемнения спрайта со временем
            button.setColor(sf::Color(button_st.alpha, button_st.alpha, button_st.alpha, 255)); // Установка новой прозрачности спрайта
            button_st.procAnim = 1;
            button_st.changedButton = 0;
        }
        else if (button_st.alpha == 0)
        {
            button.setTexture(button_hT);
            button_st.alpha = 255;
            button.setColor(sf::Color(button_st.alpha, button_st.alpha, button_st.alpha, 255));
            button_st.changedButton = 1;
            button_st.procAnim = 0;
        }
        if (button_st.procAnim and button_st.changedButton and button_st.alpha < 255)
        {
            button_st.alpha += speed;
            button.setColor(sf::Color(button_st.alpha, button_st.alpha, button_st.alpha, 255)); // Установка новой прозрачности спрайта
            if (button_st.alpha == 255) { button_st.procAnim = 0; }
        }
    }
    else
    {
        if (button_st.procAnim and !button_st.changedButton) // Плавная отмена анимации затемнения
        {
            button_st.alpha += speed;
            button.setColor(sf::Color(button_st.alpha, button_st.alpha, button_st.alpha, 255)); // Установка новой прозрачности спрайта
            if (button_st.alpha == 255) { button_st.procAnim = 0; }
        }

        if (button_st.alpha > 0 and button_st.changedButton) // Затемняем нажатую
        {
            button_st.alpha -= speed;
            button.setColor(sf::Color(button_st.alpha, button_st.alpha, button_st.alpha, 255));
            button_st.procAnim = 1;
            if (button_st.alpha == 0) { button_st.procAnim = 0; }
        }

        else if (button_st.alpha < 255 and !button_st.procAnim) // Возвращаем зеленую плавно
        {
            button_st.alpha += speed;
            button.setTexture(buttonT);
            button.setColor(sf::Color(button_st.alpha, button_st.alpha, button_st.alpha, 255));
            button_st.changedButton = 0;
        }
    }
}

bool Reminder::ShowRegisterField(sf::RenderWindow& mainWindow, sf::Sprite& button_log, sf::Sprite& button_reg, sf::Sprite& logo, sf::Sprite& log_field, sf::Sprite& pass_field, bool& reg)
{

    static double start_pos = button_reg.getPosition().y;
    double dist = button_reg.getPosition().y;
    double PosX = button_reg.getPosition().x;

    static double start_pos_logo = logo.getPosition().y;
    double dist_logo = logo.getPosition().y;
    double PosX_logo = logo.getPosition().x;

    double swipe_speed = mainWindow.getSize().x / 400.0;
    double swipe_speed_logo = mainWindow.getSize().x / 1000.0;

    sf::IntRect TextureRect = button_log.getTextureRect();  // запоминаем
    button_log.setTextureRect(sf::IntRect(0, 0, 0, 0));      // скрываем
   

    if (dist - start_pos >= mainWindow.getSize().x / 10.0)
    {
        log_field.setColor(sf::Color(255, 255, 255, 255));
        pass_field.setColor(sf::Color(255, 255, 255, 255));
        //reg = 0;
        return 1;
    }

    dist += swipe_speed;
    sf::Vector2f newPosition = sf::Vector2f(PosX, dist); // Новая позиция спрайта с учетом смещения вниз
    button_reg.setPosition(newPosition);

    dist_logo -= swipe_speed_logo;
    sf::Vector2f newPosition_logo = sf::Vector2f(PosX_logo, dist_logo);
    logo.setPosition(newPosition_logo);

    return 0;
}

void Reminder::BoneReturn()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Drag and Drop Demo with Animation");
    sf::Texture texture;
    window.setFramerateLimit(120);
    if (!texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Github icon.png")) {
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::Vector2f startPosition(400.f, 200.f); // Начальная позиция спрайта
    sprite.setPosition(startPosition);

    bool isDragging = false;
    sf::Vector2f oldPos;
    bool returnToStart = false;
    const float acceleration = 0.2f; // Ускорение возврата
    sf::Vector2f velocity(0.f, 0.f); // Скорость возврата

    // Определение границ области для спрайта
    constexpr float leftBound = 0.f;
    constexpr float rightBound = 800.f;
    constexpr float topBound = 0.f;
    constexpr float bottomBound = 600.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        isDragging = true;
                        returnToStart = false;
                        oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left && isDragging) {
                    isDragging = false;
                    returnToStart = true;
                }
                break;

            case sf::Event::MouseMoved:
                if (isDragging) {
                    const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    const sf::Vector2f deltaPos = newPos - oldPos;
                    sf::Vector2f newPosition = sprite.getPosition() + deltaPos;

                    // Ограничение движения спрайта границами окна
                    newPosition.x = std::max(leftBound, std::min(newPosition.x, rightBound - sprite.getGlobalBounds().width));
                    newPosition.y = std::max(topBound, std::min(newPosition.y, bottomBound - sprite.getGlobalBounds().height));

                    sprite.setPosition(newPosition);
                    oldPos = newPos;
                }
                break;
            }
        }
        if (returnToStart) {
            sf::Vector2f direction = startPosition - sprite.getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (length > 2) {
                direction /= length;
                // Плавное уменьшение скорости, когда спрайт приближается к начальной позиции
                velocity += direction * acceleration;
                float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
                if (speed * speed > length) {
                    // Уменьшение скорости, если она слишком велика по сравнению с оставшимся расстоянием
                    speed = std::sqrt(length);
                    velocity = direction * speed;
                }
                sprite.move(velocity);
            }
            else {
                sprite.setPosition(startPosition);
                returnToStart = false;
                velocity = sf::Vector2f(0.f, 0.f); // Сброс скорости
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

bool Reminder::JumpAnim(sf::RenderWindow& mainWindow, sf::Sprite& button_log, sf::Sprite& button_reg, sf::Sprite& logo, sf::Sprite& log_field, sf::Sprite& pass_field)
{
    // Ускорение и скорость для каждого спрайта
    float acceleration = mainWindow.getSize().x / 500.0;
    float static velocity_st = mainWindow.getSize().x / 300.0;
    float static velocity = mainWindow.getSize().x / 300.0;

    // Перемещение спрайтов с ускорением
    button_log.move(velocity, 0);
    button_reg.move(-velocity, 0);
    logo.move(0, -velocity);
    log_field.move(-velocity, 0);
    pass_field.move(velocity, 0);

    // Увеличение скорости
    velocity += acceleration;

    // Получение размеров окна
    sf::Vector2u windowSize = mainWindow.getSize();

    // Проверка, вышли ли спрайты за пределы окна
    if (button_log.getPosition().x - 300 > windowSize.x and button_reg.getPosition().x + 300 < 0
        and logo.getPosition().y + 300 < 0 and log_field.getPosition().x + 100 < 0 and pass_field.getPosition().x - 300 > windowSize.x)
    {
        velocity = velocity_st;
        return true;
    }

    return false;
}