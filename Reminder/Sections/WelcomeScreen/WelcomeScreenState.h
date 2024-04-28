#ifndef WELCOMWSCREENSTATE_H
#define  WELCOMWSCREENSTATE_H

#include "../Main menu/MainMenuState.h"

class WelcomeScreenState :
	public State
{
private:
	sf::Sprite bg;
	sf::Font font;
	sf::Event sfEvent;
	std::map<std::string, UI::Button*> buttons;
	std::map<std::string, UI::TextBox*> textboxes;
	float scale = 1;

	//Inits
	void InitVars();
	void InitBG();
	void InitFonts();
	void InitButtons();
	void InitTextBoxes();
	void InitTextures();
	void InitSprites();

	bool animTransit = 0;
	bool animTransitReverse = 0;


public:
	void Update(const float& dt);
	void UpdateKeyBoardBinds(const float& dt);
	void UpdateButtons();
	void UpdateSprites();
	void UpdateEvents();
	void UpdateTextBoxesEvent();

	void RenderButtons(sf::RenderTarget* target = nullptr);
	void RenderSprites(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr);
	void RenderTextBoxes(sf::RenderTarget* target = nullptr);
	void EndState();

	WelcomeScreenState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~WelcomeScreenState();

	void AnimOpenFields();
	void AnimCloseFields();
};

#endif
