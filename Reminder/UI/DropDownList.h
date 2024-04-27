#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.h"

namespace UI
{
	class DropDownList
	{
	private:
		UI::Button* activeElement;
		std::vector<UI::Button*> list;
		sf::Font* font;

		bool showList;
		float keyTime;
		float keyTimeMax;

		sf::Texture idleTexture;
		sf::Texture hoveredTexture;
		sf::Texture pressedTexture;

	public:
		DropDownList(float scale, unsigned nrOfElement, unsigned def_index, float x, float y, sf::Font* font,
			std::string list[], sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture pressedTexture);
		~DropDownList();

		void Render(sf::RenderTarget* target) const;
		void Update(const sf::Vector2f mousePosition, const float& dt);

		const bool getKeyTime();
		void UpdateKeyTime(const float& dt);
	};

}