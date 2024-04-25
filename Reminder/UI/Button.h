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

		sf::Font* font;
		sf::Text text;

		sf::Texture idleTexture;
		sf::Texture hoveredTexture;
		sf::Texture pressedTexture;

		sf::Sprite sprite;

	public:
		float animSpeed = 8.5;

		Button(float x, float y, float width, float height, sf::Font* font, sf::String text, sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture pressedTexture);
		
		~Button();

		void Render(sf::RenderTarget* target) const;

		void Update(const sf::Vector2f mousePosition);

		void SmoothAnim_black(float& animSpeed);
		void SmoothAnim_light(float& animSpeed);
		
		const bool isPressed() const;
	};
}