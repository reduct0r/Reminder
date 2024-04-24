#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../../State.h"

class MainMenuState :
	public State
{
private:
	//MainMenuState(sf::RenderWindow* window);
	//virtual ~MainMenuState();

public:
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
	void UpdateKeyBoardBinds(const float& dt);
	void EndState();

	MainMenuState(sf::RenderWindow* window);
	virtual ~MainMenuState();
};

#endif
