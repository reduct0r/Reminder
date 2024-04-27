#ifndef STATE_H
#define STATE_H

/* �������� ����� ��������� */

#include<vector>
#include<map>
#include<stack>
#include<fstream>
#include<sstream>
#include "../../UI/DropDownList.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class State
{
private:

protected:
	sf::RenderWindow* window;						// ������� ����
	std::map<std::string,sf::Texture> textures;		// ����� ������� ��� �������� ������
	std::unordered_map<std::string, sf::Sprite> sprites;		// ����� �������� ��� �������� ������, �� ������� background
	bool ToQuit;									// �����?

	sf::Vector2i MousePosScreen;
	sf::Vector2i MousePosWindow;
	sf::Vector2f MousePosView;

	std::stack<State*>* states;						//orig

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);				// �����������
	virtual ~State();								// ����������

	const bool getQuit() const;						

	virtual void Update(const float& dt) = 0;						// ���������� (�����)
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;	// ������
	virtual void UpdateKeyBoardBinds(const float& dt) = 0;			// �������
	virtual void UpdateMousePos();

	virtual void CheckForQuit();					// �����?						
	virtual void EndState();						// ����� ������

};

#endif