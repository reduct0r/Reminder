#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.h"

namespace ReminderUI
{
	class DropDownList
	{
	private:
		ReminderUI::Button* activeElement;
		std::vector<ReminderUI::Button*> list;
		sf::Font* font;

		bool showList;
		float keyTime;
		float keyTimeMax;

		sf::Texture idleTexture;
		sf::Texture hoveredTexture;
		sf::Texture chooseTexture;

	public:
		DropDownList(float scale, unsigned def_index, float x, float y, sf::Font* font, float fontSize,
			std::vector<std::string> list, sf::Texture idleTexture, sf::Texture hoveredTexture, sf::Texture chooseTexture);
		~DropDownList();

		void Render(sf::RenderTarget* target) const;
		void Update(const sf::Vector2f mousePosition, const float& dt);

		const bool getKeyTime();
		const unsigned short& getActiveElementId() const;
		void UpdateKeyTime(const float& dt);
		void Hide(bool flag, float scale);
	};

}