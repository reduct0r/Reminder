#pragma once
#include <SFML/Graphics.hpp>
//TEST
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
}