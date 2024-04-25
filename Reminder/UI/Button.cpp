#include "Button.h"

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


void UI::Button::Update(const sf::Vector2f mousePosition, float alpha, bool changedButton, bool procAnim)
{
	/* IDLE */
    this->ButtonState = BTN_IDLE;

    float speed = 8.5;

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
		this->sprite.setTexture(this->idleTexture);
		break;

	case BTN_HOVER:
		this->sprite.setTexture(this->hoveredTexture);
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


// ******
//if (button.getGlobalBounds().contains(mousePosition))
//{
//    this->ButtonState = BTN_HOVER;
//
//
//    if (alpha > 0 and !changedButton)
//    {
//        alpha -= speed; // Изменение затемнения спрайта со временем
//        button.setColor(sf::Color(alpha, alpha, alpha, 255)); // Установка новой прозрачности спрайта
//        procAnim = 1;
//        changedButton = 0;
//    }
//    else if (alpha == 0)
//    {
//        button.setTexture(this->hoveredTexture);
//        alpha = 255;
//        button.setColor(sf::Color(alpha, alpha, alpha, 255));
//        changedButton = 1;
//        procAnim = 0;
//    }
//    if (procAnim and changedButton and alpha < 255)
//    {
//        alpha += speed;
//        button.setColor(sf::Color(alpha, alpha, alpha, 255)); // Установка новой прозрачности спрайта
//        if (alpha == 255) { procAnim = 0; }
//    }
//}
//else
//{
//    if (procAnim and !changedButton) // Плавная отмена анимации затемнения
//    {
//        alpha += speed;
//        button.setColor(sf::Color(alpha, alpha, alpha, 255)); // Установка новой прозрачности спрайта
//        if (alpha == 255) { procAnim = 0; }
//    }
//
//    if (alpha > 0 and changedButton) // Затемняем нажатую
//    {
//        alpha -= speed;
//        button.setColor(sf::Color(alpha, alpha, alpha, 255));
//        procAnim = 1;
//        if (alpha == 0) { procAnim = 0; }
//    }
//
//    else if (alpha < 255 and !procAnim) // Возвращаем зеленую плавно
//    {
//        alpha += speed;
//        button.setTexture(this->idleTexture);
//        button.setColor(sf::Color(alpha, alpha, alpha, 255));
//        changedButton = 0;
//    }
//}