#ifndef STATE_H
#define STATE_H

/* Основной класс состояния */

#include<vector>
#include<map>
#include<stack>
#include <SFML/Graphics.hpp>

class State
{
private:
	sf::RenderWindow* window;						// Текущее окно
	std::vector<sf::Texture> textures;				// Набор текстур для текущего стейта
	bool ToQuit;									// Выход?

public:
	State(sf::RenderWindow* window);				// Конструктор
	virtual ~State();								// Деструктор

	const bool getQuit() const;						

	virtual void Update(const float& dt) = 0;						// Обновление (опрос)
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;	// Рендер
	virtual void UpdateKeyBoardBinds(const float& dt) = 0;			// Клавиши

	virtual void CheckForQuit();					// Выйти?						
	virtual void EndState();						// Стейт выхода

};

#endif