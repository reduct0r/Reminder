#ifndef STATE_H
#define STATE_H

/* Основной класс состояния */

#include<vector>
#include<map>
#include<stack>
#include<fstream>
#include<sstream>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

#include "../../UI/DropDownList.h"
#include "../../UI/TextBox.h"
#include"Settings.h"

class State
{
private:

protected:
	sf::RenderWindow* window;									// Текущее окно
	std::map<std::string,sf::Texture> textures;					// Набор текстур для текущего стейта
	std::unordered_map<std::string, sf::Sprite> sprites;		// Набор спрайтов для текущего стейта, не включая background
												

	sf::Vector2i MousePosScreen;
	sf::Vector2i MousePosWindow;
	sf::Vector2f MousePosView;

	std::stack<State*>* states;									//orig

	bool ToQuit;												// Выход?
	float keyTime;
	float keyTimeMax;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);				// Конструктор
	virtual ~State();															// Деструктор

	const bool getQuit() const;						
	const bool getKeyTime();


	virtual void Update(const float& dt) = 0;						// Обновление (опрос)
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;	// Рендер
	virtual void UpdateKeyBoardBinds(const float& dt) = 0;			// Клавиши
	virtual void UpdateMousePos();
	virtual void UpdateKeyTime(const float& dt);

	virtual void CheckForQuit();					// Выйти?						
	virtual void EndState();						// Стейт выхода

};

#endif