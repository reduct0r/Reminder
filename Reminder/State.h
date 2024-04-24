#ifndef STATE_H
#define STATE_H

/* �������� ����� ��������� */

#include<vector>
#include<map>
#include<stack>
#include <SFML/Graphics.hpp>

class State
{
private:
	sf::RenderWindow* window;						// ������� ����
	std::vector<sf::Texture> textures;				// ����� ������� ��� �������� ������
	bool ToQuit;									// �����?

public:
	State(sf::RenderWindow* window);				// �����������
	virtual ~State();								// ����������

	const bool getQuit() const;						

	virtual void Update(const float& dt) = 0;						// ���������� (�����)
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;	// ������
	virtual void UpdateKeyBoardBinds(const float& dt) = 0;			// �������

	virtual void CheckForQuit();					// �����?						
	virtual void EndState();						// ����� ������

};

#endif