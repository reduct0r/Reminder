#include <SFML/Graphics.hpp>
namespace ReminderUI {
enum ButtonStates {
  BTN_IDLE = 0,
  BTN_HOVER,
  BTN_ACTIVE
};

class Button {
 private:
  short unsigned ButtonState;
  short unsigned id = 0;

  float alpha = 255;
  bool hide = 0;
  bool changedButton = 0;
  bool procAnim = 0;
  bool needAnim = 1;
  float dt;

  sf::Font *font;
  sf::Text text;

  sf::Texture idleTexture;
  sf::Texture hoveredTexture;
  sf::Texture pressedTexture;

  sf::Sprite sprite;
  sf::Clock dtClock;

 public:
  float animSpeed = 8.5;

  Button(float x,
         float y,
         float scale,
         sf::Texture idleTexture,
         sf::Texture hoveredTexture,
         sf::Texture pressedTexture);
  Button(bool needAnim,
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
         short unsigned id = 0);
  ~Button();

  void Render(sf::RenderTarget *target) const;

  void Update(const sf::Vector2f mousePosition);
  void UpdateDT();

  void SmoothAnim_black(float &animSpeed);
  void SmoothAnim_light(float &animSpeed);

  void Hide(bool flag);
  void setPos(sf::Vector2f &vector);
  void setPos(float x, float y);
  void setId(const short unsigned id);
  void setText(const sf::String text);
  void setNewTextures(sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture pressedTexture);

  bool moveA(float scale, sf::Vector2f targetPosition, float distances, sf::Vector2f startPositions, float dir);

  sf::Vector2f getPos();
  const bool isPressed() const;
  const std::string getText() const;
  const short unsigned &getId() const;
};
}