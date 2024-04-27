#include <SFML/Graphics.hpp>

namespace UI 
{
	enum ButtonStates 
	{
		BTN_IDLE = 0,
		BTN_HOVER,
		BTN_ACTIVE
	};

	class Button
	{
	private:
		short unsigned ButtonState;
		float alpha = 255;
		bool changedButton = 0;
		bool procAnim = 0;

		//float dt;

		sf::Font* font;
		sf::Text text;

		sf::Texture idleTexture;
		sf::Texture hoveredTexture;
		sf::Texture pressedTexture;

		sf::Sprite sprite;
		//sf::Clock dtClock;

	public:
		float animSpeed = 8.5;

		Button(float x, float y, float width, float height, sf::Font* font, sf::String text, sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture pressedTexture);
		
		~Button();

		void Render(sf::RenderTarget* target) const;

		void Update(const sf::Vector2f mousePosition);
		void UpdateDT();

		void SmoothAnim_black(float& animSpeed);
		void SmoothAnim_light(float& animSpeed);

		void Hide(bool flag);
		void setPos(sf::Vector2f& vector);
		void setPos(float x, float y);
		sf::Vector2f getPos();
		
		const bool isPressed() const;
	};
}