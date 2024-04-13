#include "UI_anims.h"
#include <iostream>
//TEST
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