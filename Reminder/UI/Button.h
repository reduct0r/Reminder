#include <SFML/Graphics.hpp>

namespace UI 
{
	class Button
	{
	private:
		float alpha = 255;
		bool changedButton = 0;
		bool procAnim = 0;

		sf::Font* font;
		sf::Text text;

		sf::Texture idleTexture;
		sf::Texture hoveredTexture;

		sf::Sprite sprite;

	public:
		Button(float x, float y, float width, float height, sf::Font* font, sf::String& text, sf::Texture& idleTexture, sf::Texture& hoveredTexture);
		
		~Button();

		void Render(sf::RenderTarget* target) const;

		void Update(const sf::Vector2f mousePosition, float alpha, bool changedButton, bool procAnim);

		//void SmoothAnim(sf::Vector2f mousePosition, ButtonState& button_st);  
	};
}