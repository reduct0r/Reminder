#ifndef STATE_H
#define STATE_H

/* �������� ����� ��������� */

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

class State {
 private:

 protected:
  sf::RenderWindow *window;                                    // ������� ����
  std::map<std::string, sf::Texture> textures;                    // ����� ������� ��� �������� ������
  std::unordered_map<std::string, sf::Sprite>
      sprites;        // ����� �������� ��� �������� ������, �� ������� background


  sf::Vector2i MousePosScreen;
  sf::Vector2i MousePosWindow;
  sf::Vector2f MousePosView;

  std::stack<State *> *states;                                    //orig

  bool ToQuit;                                                // �����?
  float keyTime;
  float keyTimeMax;

 public:
  State(sf::RenderWindow *window, std::stack<State *> *states);                // �����������
  virtual ~State();                                                            // ����������

  const bool getQuit() const;
  const bool getKeyTime();

  virtual void Update(const float &dt) = 0;                        // ���������� (�����)
  virtual void Render(sf::RenderTarget *target = nullptr) = 0;    // ������
  virtual void UpdateKeyBoardBinds(const float &dt) = 0;            // �������
  virtual void UpdateMousePos();
  virtual void UpdateKeyTime(const float &dt);

  virtual void CheckForQuit();                    // �����?
  virtual void EndState();                        // ����� ������

};

#endif