#include "DropDownList.h"

UI::DropDownList::DropDownList(float scale, unsigned nrOfElement, unsigned def_index, float x, float y, sf::Font* font,
	std::string list[], sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture pressedTexture)
	:font(font), showList(false), keyTimeMax(1.0), keyTime(0), idleTexture(idleTexture), hoveredTexture(hoveredTexture),
	pressedTexture(hoveredTexture)
{
	for (size_t i = 0; i < nrOfElement; i++)
	{
		this->list.push_back(new Button(x, y + (i * idleTexture.getSize().y * scale),  scale, scale, font, list[i],
			idleTexture, hoveredTexture, pressedTexture));
	}

	this->activeElement = new Button(*this->list[def_index]);
	
}

UI::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (auto*& it : this->list)
	{
		delete it;
	}
}

void UI::DropDownList::Update(const sf::Vector2f mousePosition, const float& dt)
{
	this->UpdateKeyTime(dt);

	this->activeElement->Update(mousePosition);

	// show and hide list
	if (this->activeElement->isPressed() and this->getKeyTime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;

	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->Update(mousePosition);
		}
	}
}

const bool UI::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0;
		return true;
	}
	return false;
}

void UI::DropDownList::UpdateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10 * dt;
	}
}

void UI::DropDownList::Render(sf::RenderTarget* target) const
{
	this->activeElement->Render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->Render(target);
		}
	}
}