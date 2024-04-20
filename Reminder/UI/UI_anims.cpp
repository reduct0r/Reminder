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

    double swipe_speed = 2;
    double swipe_speed_logo = 1;

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
