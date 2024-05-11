#pragma once
#include "../../State.h"

class SettingsState :
	public State
{
private:
	Settings& gfxSettings;

	sf::Sprite bg;
	sf::Font font;
	sf::Event sfEvent;
	std::map<std::string, ReminderUI::Button*> buttons;
	std::map<std::string, ReminderUI::DropDownList*> dropDownLists;
	std::vector<sf::VideoMode> videoModes;
	
	float scale = 1;

	//Inits
	void InitVars();
	void InitBG();
	void InitFonts();
	void InitButtons();
	void InitTextures();
	void InitSprites();
	void InitDropDownLists();


public:
	SettingsState(sf::RenderWindow* window, std::stack<State*>* states, Settings& gfxSettings);
	virtual ~SettingsState();

	void Update(const float& dt);
	void UpdateButtons();
	void UpdateSprites();
	void UpdateEvents();
	void UpdateKeyBoardBinds(const float& dt);
	void UpdateDropDownLists(const float& dt);

	void RenderButtons(sf::RenderTarget* target = nullptr);
	void RenderSprites(sf::RenderTarget* target = nullptr);
	void RenderDropDownLists(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr);

};