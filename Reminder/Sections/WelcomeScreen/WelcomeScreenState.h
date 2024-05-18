#ifndef WELCOMWSCREENSTATE_H
#define  WELCOMWSCREENSTATE_H

#include "../Main menu/MainMenuState.h"
#include "../../Auth/Database.h"
#include "../../Auth/Model/UserDAO.h"
#include "../../Auth/Service/SessionIdService.h"

class WelcomeScreenState :
	public State
{
private:
	Settings& gfxSettings;

	sf::Sprite bg;
	sf::Font font;
	sf::Event sfEvent;
	std::map<std::string, ReminderUI::Button*> buttons;
	std::map<std::string, ReminderUI::TextBox*> textboxes;
	std::unordered_map<std::string, sf::Vector2f> targetPositions;
	std::map<std::string, float> distances;
	std::map<std::string, sf::Vector2f> startPositions;

	sf::Clock dtClock;
	float dt;
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
	void UpdateDT();
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

	WelcomeScreenState(sf::RenderWindow* window, std::stack<State*>* states, Settings& gfxSettings);
	virtual ~WelcomeScreenState();

	void MoveSprites(float dir);
};
#endif
