#pragma once
#include "SettingsState.h"
#include "../../State.h"

class PresetsMenuState :
	public State
{
private:
	Settings& gfxSettings;

	sf::Sprite bg;
	sf::Font font;
	sf::Event sfEvent;
	std::map<std::string, ReminderUI::Button*> buttons;
	std::map<std::string, ReminderUI::DropDownList*> dropDownLists;
	std::map<std::string, sf::Text> textes;
	std::vector<std::string> presets;

	float scale = 1;
	bool startFullScreen = 0;

	//Inits
	void InitVars();
	void InitBG();
	void InitFonts();
	void InitButtons();
	void InitTextures();
	void InitSprites();
	void InitTextes();
	void InitDropDownLists();


public:
	PresetsMenuState(sf::RenderWindow* window, std::stack<State*>* states, Settings& gfxSettings);
	virtual ~PresetsMenuState();

	void Update(const float& dt);
	void UpdateButtons();
	void UpdateSprites();
	void UpdateEvents();
	void UpdateKeyBoardBinds(const float& dt);
	void UpdateDropDownLists(const float& dt);

	void RenderButtons(sf::RenderTarget* target = nullptr);
	void RenderSprites(sf::RenderTarget* target = nullptr);
	void RenderDropDownLists(sf::RenderTarget* target = nullptr);
	void RenderTextes(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr);
	void EndState();
};
