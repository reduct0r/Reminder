#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../../State.h"

class MainMenuState :
	public State
{
private:
	sf::RectangleShape bg;
	sf::Font font;
	std::map<std::string, UI::Button*> buttons;

	//Inits
	void InitFonts();
	void InitButtons();


public:
	void Update(const float& dt);
	void UpdateKeyBoardBinds(const float& dt);
	void UpdateButtons();

	void RenderButtons(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr);

	void EndState();

	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();
};

#endif
