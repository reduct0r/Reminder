#ifndef WELCOMWSCREENSTATE_H
#define  WELCOMWSCREENSTATE_H

#include "../../State.h"
class WelcomeScreenState :
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

	WelcomeScreenState(sf::RenderWindow* window);
	virtual ~WelcomeScreenState();
};

#endif
