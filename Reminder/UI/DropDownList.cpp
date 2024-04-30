#include "DropDownList.h"
#include <iterator>

UI::DropDownList::DropDownList(float scale, unsigned def_index, float x, float y, sf::Font* font, float fontSize,
	std::vector<std::string> list, sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture chooseTexture)
	:font(font), showList(false), keyTimeMax(1.0), keyTime(0), idleTexture(idleTexture), hoveredTexture(hoveredTexture),
	chooseTexture(chooseTexture)
{
	unsigned nrOfElement = list.size();

	this->activeElement = new UI::Button(0, fontSize * 2 * scale, x, y + idleTexture.getSize().y * scale, scale, scale, font, list[def_index],
		chooseTexture, hoveredTexture, chooseTexture);

	for (size_t i = 0; i < nrOfElement; i++)
	{
		this->list.push_back(new UI::Button(0, fontSize * 2 * scale,x, y + ((i+1) * idleTexture.getSize().y * scale),  scale, scale, font, list[i],
			idleTexture, hoveredTexture, chooseTexture, i));
	}

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

			if (i->isPressed() and this->getKeyTime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}

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

const unsigned short& UI::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
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