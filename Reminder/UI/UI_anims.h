#pragma once
#include <SFML/Graphics.hpp>
#include "../UI/TextBox.h"

namespace Reminder {
struct ButtonState {
  float alpha = 255;
  bool changedButton = 0;
  bool procAnim = 0;
};

void SmoothButtonAnim(sf::Sprite &button,
                      sf::Vector2i &mousePosition,
                      sf::Texture &buttonT,
                      sf::Texture &button_hT,
                      ButtonState &button_st);
bool ShowRegisterField(sf::RenderWindow &mainWindow,
                       sf::Sprite &button_log,
                       sf::Sprite &button_reg,
                       sf::Sprite &logo,
                       sf::Sprite &log_field,
                       sf::Sprite &pass_field,
                       bool &reg);
void BoneReturn();
bool JumpAnim(sf::RenderWindow &mainWindow,
              sf::Sprite &button_log,
              sf::Sprite &button_reg,
              sf::Sprite &logo,
              sf::Sprite &log_field,
              sf::Sprite &pass_field);
}