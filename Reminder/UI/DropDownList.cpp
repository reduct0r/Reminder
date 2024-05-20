#include "DropDownList.h"
#include <iterator>

ReminderUI::DropDownList::DropDownList(float scale,
                                       unsigned def_index,
                                       float x,
                                       float y,
                                       sf::Font *font,
                                       float fontSize,
                                       std::vector<std::string> list,
                                       sf::Texture idleTexture,
                                       sf::Texture hoveredTexture,
                                       sf::Texture chooseTexture)
    : font(font),
      showList(false),
      keyTimeMax(1.0),
      keyTime(0),
      idleTexture(idleTexture),
      hoveredTexture(hoveredTexture),
      chooseTexture(chooseTexture) {
  unsigned nrOfElement = list.size();

  this->activeElement = new ReminderUI::Button(0,
                                               fontSize,
                                               x,
                                               y + idleTexture.getSize().y * scale,
                                               scale,
                                               scale,
                                               font,
                                               list[def_index],
                                               chooseTexture,
                                               hoveredTexture,
                                               chooseTexture);

  for (size_t i = 0; i < nrOfElement; i++) {
    this->list.push_back(new ReminderUI::Button(0,
                                                fontSize,
                                                x,
                                                y + ((i + 1) * idleTexture.getSize().y * scale),
                                                scale,
                                                scale,
                                                font,
                                                list[i],
                                                idleTexture,
                                                hoveredTexture,
                                                chooseTexture,
                                                i));
  }

}

ReminderUI::DropDownList::~DropDownList() {
  delete this->activeElement;
  for (auto *&it : this->list) {
    delete it;
  }
}

void ReminderUI::DropDownList::Update(const sf::Vector2f mousePosition, const float &dt) {
  this->UpdateKeyTime(dt);

  this->activeElement->Update(mousePosition);

  // show and hide list
  if (this->activeElement->isPressed() and this->getKeyTime()) {
    if (this->showList)
      this->showList = false;
    else
      this->showList = true;

  }

  if (this->showList) {
    for (auto &i : this->list) {
      i->Update(mousePosition);

      if (i->isPressed() and this->getKeyTime()) {
        this->showList = false;
        this->activeElement->setText(i->getText());
        this->activeElement->setId(i->getId());
      }

    }
  }
}

const bool ReminderUI::DropDownList::getKeyTime() {
  if (this->keyTime >= this->keyTimeMax) {
    this->keyTime = 0;
    return true;
  }
  return false;
}

const unsigned short &ReminderUI::DropDownList::getActiveElementId() const {
  return this->activeElement->getId();
}

void ReminderUI::DropDownList::UpdateKeyTime(const float &dt) {
  if (this->keyTime < this->keyTimeMax) {
    this->keyTime += 10 * dt;
  }
}

void ReminderUI::DropDownList::Hide(bool flag) {
  this->activeElement->Hide(flag);
}

void ReminderUI::DropDownList::Blink()
{
    this->activeElement->setText("CHOOSE PRESET!");
}

void ReminderUI::DropDownList::setActiveEl(int i)
{
    this->activeElement->setText(this->list[i - 1]->getText());
}

void ReminderUI::DropDownList::Render(sf::RenderTarget *target) const {
  this->activeElement->Render(target);

  if (this->showList) {
    for (auto &i : this->list) {
      i->Render(target);
    }
  }
}