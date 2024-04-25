#include "Button.h"
#include <iostream>

UI::Button::Button(float x, float y, float width, float height, sf::Font* font, sf::String text, sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture pressedTexture)
{
    this->ButtonState = BTN_IDLE;
	this->idleTexture = idleTexture;
	this->hoveredTexture = hoveredTexture;
	this->pressedTexture = pressedTexture;
	this->font = font;

	this->sprite.setTexture(this->idleTexture);
	this->sprite.setPosition(sf::Vector2f(x, y));
	this->sprite.setScale(width, height);

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setColor(sf::Color::Black);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2.0) - this->text.getGlobalBounds().width / 2.0,
		this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2.0)  - this->text.getGlobalBounds().height / 2.0
	);


}

UI::Button::~Button()
{
}


void UI::Button::Update(const sf::Vector2f mousePosition)
{
	/* IDLE */
    this->ButtonState = BTN_IDLE;

    sf::Sprite button= this->sprite;

    /* HOVER */
	if (button.getGlobalBounds().contains(mousePosition))
	{
		this->ButtonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->ButtonState = BTN_ACTIVE;
		}
	}

	switch (this->ButtonState)
	{
	case BTN_IDLE:
		//this->sprite.setTexture(this->idleTexture);
        UI::Button::SmoothAnim_light(this->animSpeed);
		break;

	case BTN_HOVER:
		//this->sprite.setTexture(this->hoveredTexture);
		UI::Button::SmoothAnim_black(this->animSpeed);
		break;

	case BTN_ACTIVE:
		this->sprite.setTexture(this->pressedTexture);
        
		break;

	default:
		this->sprite.setColor(sf::Color::Red);
		break;
	}
}


const bool UI::Button::isPressed() const
{
	if (this->ButtonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

void UI::Button::Render(sf::RenderTarget* target) const
{
	target->draw(this->sprite);
	target->draw(this->text);
}

void UI::Button::SmoothAnim_black(float& animSpeed)
{
    //sf::Sprite button;
    //if (BTN_HOVER)
    {
        if (this->alpha > 0 and !this->changedButton)
        {
            this->alpha -= animSpeed; // Изменение затемнения спрайта со временем
            this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255)); // Установка новой прозрачности спрайта
            this->procAnim = 1;
            this->changedButton = 0;
        }
        else if (this->alpha == 0)
        {
            this->sprite.setTexture(this->hoveredTexture);
            this->alpha = 255;
            this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255));
            this->changedButton = 1;
            this->procAnim = 0;
        }
        if (this->procAnim and this->changedButton and this->alpha < 255)
        {
            this->alpha += animSpeed;
            this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255)); // Установка новой прозрачности спрайта
            if (this->alpha == 255) { this->procAnim = 0; }
        }
    }
}

 void UI::Button::SmoothAnim_light(float& animSpeed)
 {
        if (this->procAnim and !this->changedButton) // Плавная отмена анимации затемнения
        {
            this->alpha += animSpeed;
            this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255)); // Установка новой прозрачности спрайта
            if (this->alpha == 255) { this->procAnim = 0; }
        }

        if (this->alpha > 0 and this->changedButton) // Затемняем нажатую
        {
            this->alpha -= animSpeed;
            this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255));
            this->procAnim = 1;
            if (this->alpha == 0) { this->procAnim = 0; }
        }

        else if (this->alpha < 255 and !this->procAnim) // Возвращаем зеленую плавно
        {
            this->alpha += animSpeed;
            this->sprite.setTexture(this->idleTexture);
            this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255));
            this->changedButton = 0;
        }
}
