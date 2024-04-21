#include "Button.h"

UI::Button::Button(float x, float y, float width, float height, sf::Font* font, sf::String& text, sf::Texture& idleTexture, sf::Texture& hoveredTexture)
{
    /*this->hovered = 0;
    this->pressed = 0;*/

	this->sprite.setTexture(idleTexture);
	this->sprite.setPosition(sf::Vector2f(x, y));

	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setColor(sf::Color::Black);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		this->sprite.getPosition().x / 2.0 - this->text.getGlobalBounds().width / 2.0,
		this->sprite.getPosition().y / 2.0 - this->text.getGlobalBounds().height / 2.0
	);

	this->idleTexture = idleTexture;
	this->hoveredTexture = hoveredTexture;
}

UI::Button::~Button()
{
}

void UI::Button::Render(sf::RenderTarget* target) const
{
	target->draw(this->sprite);
}

//void UI::Button::Update(const sf::Vector2f mousePos, ButtonState& button_st)
//{
//	// Update button status
//	
//	this->hovered = 0;
//	this->pressed = 0;
//
//	if (this->sprite.getGlobalBounds().contains(mousePos))	// HOVER
//	{
//		this->hovered = 1;
//
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))	// PRESS
//		{
//			this->pressed = 1;
//		}
//	}
//
//	if (hovered)
//	{
//		UI::Button::SmoothAnim(mousePos, button_st);
//	}
//
//
//}

void UI::Button::Update(const sf::Vector2f mousePosition, float alpha, bool changedButton, bool procAnim)
{
    float speed = 8.5;

    sf::Sprite button= this->sprite;

    if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
    {
        if (alpha > 0 and !changedButton)
        {
            alpha -= speed; // Изменение затемнения спрайта со временем
            button.setColor(sf::Color(alpha, alpha, alpha, 255)); // Установка новой прозрачности спрайта
            procAnim = 1;
            changedButton = 0;
        }
        else if (alpha == 0)
        {
            button.setTexture(this->hoveredTexture);
            alpha = 255;
            button.setColor(sf::Color(alpha, alpha, alpha, 255));
            changedButton = 1;
            procAnim = 0;
        }
        if (procAnim and changedButton and alpha < 255)
        {
            alpha += speed;
            button.setColor(sf::Color(alpha, alpha, alpha, 255)); // Установка новой прозрачности спрайта
            if (alpha == 255) {procAnim = 0; }
        }
    }
    else
    {
        if (procAnim and !changedButton) // Плавная отмена анимации затемнения
        {
            alpha += speed;
            button.setColor(sf::Color(alpha, alpha, alpha, 255)); // Установка новой прозрачности спрайта
            if (alpha == 255) { procAnim = 0; }
        }

        if (alpha > 0 and changedButton) // Затемняем нажатую
        {
            alpha -= speed;
            button.setColor(sf::Color(alpha, alpha, alpha, 255));
            procAnim = 1;
            if (alpha == 0) { procAnim = 0; }
        }

        else if (alpha < 255 and !procAnim) // Возвращаем зеленую плавно
        {
            alpha += speed;
            button.setTexture(this->idleTexture);
            button.setColor(sf::Color(alpha, alpha, alpha, 255));
            changedButton = 0;
        }
    }
}

