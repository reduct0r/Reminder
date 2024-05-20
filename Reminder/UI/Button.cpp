#include "Button.h"
#include <iostream>
#include <unordered_map>

ReminderUI::Button::Button(float x,
                           float y,
                           float scale,
                           sf::Texture idleTexture,
                           sf::Texture hoveredTexture,
                           sf::Texture pressedTexture) {
  this->id = 0;
  this->needAnim = 1;
  this->ButtonState = BTN_IDLE;
  this->idleTexture = idleTexture;
  this->hoveredTexture = hoveredTexture;
  this->pressedTexture = pressedTexture;
  this->font = font;

  this->sprite.setTexture(this->idleTexture);
  this->sprite.setPosition(sf::Vector2f(x, y));
  this->sprite.setScale(scale, scale);

}

ReminderUI::Button::Button(bool needAnim,
                           float fontSize,
                           float x,
                           float y,
                           float width,
                           float height,
                           sf::Font *font,
                           sf::String text,
                           sf::Texture idleTexture,
                           sf::Texture hoveredTexture,
                           sf::Texture pressedTexture,
                           short unsigned id) {
  this->id = id;
  this->needAnim = needAnim;
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
  this->text.setCharacterSize(fontSize * width);
  this->text.setPosition(
      this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2.0)
          - this->text.getGlobalBounds().width / 2.0,
      this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2.0)
          - this->text.getGlobalBounds().height / 1.3
  );

}

ReminderUI::Button::~Button() {
}

void ReminderUI::Button::Update(const sf::Vector2f mousePosition) {
  UpdateDT();
  /* IDLE */
  this->ButtonState = BTN_IDLE;
  sf::Sprite button = this->sprite;

  /* HOVER */
  if (button.getGlobalBounds().contains(mousePosition)) {
    this->ButtonState = BTN_HOVER;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      this->ButtonState = BTN_ACTIVE;
    }
  }

  switch (this->ButtonState) {
    case BTN_IDLE:
      if (this->needAnim) {
        ReminderUI::Button::SmoothAnim_light(this->animSpeed);
      } else {
        this->sprite.setTexture(this->idleTexture);
      }
      break;

    case BTN_HOVER:
      if (this->needAnim) {
        ReminderUI::Button::SmoothAnim_black(this->animSpeed);
      } else {
        this->sprite.setTexture(this->hoveredTexture);
      }
      break;

    case BTN_ACTIVE:
      if (!this->needAnim) {
        this->sprite.setTexture(this->pressedTexture);
      }

      break;

    default:

      this->sprite.setColor(sf::Color::Red);
      break;
  }
}

void ReminderUI::Button::UpdateDT() {
  this->dt = this->dtClock.restart().asSeconds();
}

void ReminderUI::Button::setText(const sf::String text) {
  this->text.setString(text);
  this->text.setPosition(
      this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2.0)
          - this->text.getGlobalBounds().width / 2.0,
      this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2.0)
          - this->text.getGlobalBounds().height / 1.3
  );
}

void ReminderUI::Button::setNewTextures(sf::Texture idleTexture,
                                        sf::Texture hoveredTexture,
                                        sf::Texture pressedTexture) {
  this->idleTexture = idleTexture;
  this->hoveredTexture = hoveredTexture;
  this->pressedTexture = pressedTexture;
}

bool ReminderUI::Button::moveA(float scale,
                               sf::Vector2f targetPosition,
                               float distances,
                               sf::Vector2f startPositions,
                               float dir) {
  bool allButtonsAtTarget = true;

  if (dir == -1) {
    startPositions =
        sf::Vector2f(startPositions.x, startPositions.y + distances * targetPosition.y / abs(targetPosition.y));
  }

  sf::Vector2f vectorBetweenPoints = this->sprite.getPosition() - startPositions;
  float distanceS = std::hypot(vectorBetweenPoints.x, vectorBetweenPoints.y);

  if (distanceS <= distances) {
    allButtonsAtTarget = false;

    sf::Vector2f direction = targetPosition;
    float acceleration = 16 * scale * abs(distances - distanceS);
    if (acceleration < 5) {
      acceleration = 5;
    }
    float speed = acceleration * this->dt;

    if (distances > speed) {
      direction /= distances;
      this->sprite.move(direction * speed * dir);
    } else {
      this->sprite.setPosition(targetPosition);
    }
  }

  if (allButtonsAtTarget) {
    // return 1;
    // something return
  }

  return 1;

}

const bool ReminderUI::Button::isPressed() const {
  if (this->ButtonState == BTN_ACTIVE) {
    return true;
  }
  return false;
}

const std::string ReminderUI::Button::getText() const {
  return this->text.getString();
}

const short unsigned &ReminderUI::Button::getId() const {
  return this->id;
}

void ReminderUI::Button::Render(sf::RenderTarget *target) const {
  if (!this->hide) {
    target->draw(this->sprite);
    target->draw(this->text);
  }
}

void ReminderUI::Button::SmoothAnim_black(float &animSpeed) {

  if (this->alpha > 0 and !this->changedButton) {
    this->alpha -= animSpeed; // Изменение затемнения спрайта со временем
    this->sprite.setColor(sf::Color(this->alpha,
                                    this->alpha,
                                    this->alpha,
                                    255)); // Установка новой прозрачности спрайта
    this->procAnim = 1;
    this->changedButton = 0;
  } else if (this->alpha == 0) {
    this->sprite.setTexture(this->hoveredTexture);
    this->alpha = 255;
    this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255));
    this->changedButton = 1;
    this->procAnim = 0;
  }
  if (this->procAnim and this->changedButton and this->alpha < 255) {
    this->alpha += animSpeed;
    this->sprite.setColor(sf::Color(this->alpha,
                                    this->alpha,
                                    this->alpha,
                                    255)); // Установка новой прозрачности спрайта
    if (this->alpha == 255) { this->procAnim = 0; }
  }

}

void ReminderUI::Button::SmoothAnim_light(float &animSpeed) {
  if (this->procAnim and !this->changedButton) // Плавная отмена анимации затемнения
  {
    this->alpha += animSpeed;
    this->sprite.setColor(sf::Color(this->alpha,
                                    this->alpha,
                                    this->alpha,
                                    255)); // Установка новой прозрачности спрайта
    if (this->alpha == 255) { this->procAnim = 0; }
  }

  if (this->alpha > 0 and this->changedButton) // Затемняем нажатую
  {
    this->alpha -= animSpeed;
    this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255));
    this->procAnim = 1;
    if (this->alpha == 0) { this->procAnim = 0; }
  } else if (this->alpha < 255 and !this->procAnim) // Возвращаем зеленую плавно
  {
    this->alpha += animSpeed;
    this->sprite.setTexture(this->idleTexture);
    this->sprite.setColor(sf::Color(this->alpha, this->alpha, this->alpha, 255));
    this->changedButton = 0;
  }
}

void ReminderUI::Button::Hide(bool flag) {
  this->hide = flag;
  if (flag) {
    this->sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
  } else {
    this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                            sf::Vector2i(this->sprite.getTexture()->getSize().x,
                                                         this->sprite.getTexture()->getSize().y)));
  }
}

void ReminderUI::Button::setPos(sf::Vector2f &vector) {
  this->sprite.setPosition(vector);
}

void ReminderUI::Button::setPos(float x, float y) {
  this->sprite.setPosition(x, y);
}

void ReminderUI::Button::setId(const short unsigned id) {
  this->id = id;
}

sf::Vector2f ReminderUI::Button::getPos() {
  sf::Vector2f vector = this->sprite.getPosition();
  return vector;
}
