#ifndef REMINDER_GAMEPROCESS_H
#define REMINDER_GAMEPROCESS_H

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "json/json.h"

//
//#pragma once
//#include "../Sections/PreesetsMenu/PresetsMenu.h"
//
//class Game {
//private:
//    Settings gfxSettings;
//
//    sf::RenderWindow* window;
//    sf::Event sfEvent;
//    sf::Clock dtClock;
//    float dt;
//
//    std::stack<State*> states;
//
//    void InitVars();
//    void InitWindow();
//    void InitStates();
//    void InitSettings();
//
//public:
//    // Core
//    Game();
//    virtual ~Game();
//    void Run();
//
//    // Update
//    void Update();
//    void UpdateEvents();
//    void UpdateDT();
//
//    //Render
//    void Render();
//
//    // Functions
//    void EndApplication();
//
//};

namespace Reminder {
class Card {
 public:
  std::string title;
  std::string text;
  int number = 0;
  bool failed = false;

  Card(const Card &other) : title(other.title), text(other.text), number(other.number), failed(other.failed) {}

  Card(const std::string &title, const std::string &text) : title(title), text(text) {}

  void setTitle(const std::string &title) {
    this->title = title;
  }

  const std::string &getTitle() const {
    return title;
  }

  void setText(const std::string &text) {
    this->text = text;
  }

  const std::string &getText() const {
    return text;
  }

  void setNumber(int number) {
    this->number = number;
  }

  int getNumber() const {
    return number;
  }

  void setFailed(bool failed) {
    this->failed = failed;
  }

  bool isFailed() const {
    return failed;
  }

};

class CardPreset {
 public:
  std::vector<Card> preset;
  std::string name;
  int number = 0;

  CardPreset() : number(0) {}

  explicit CardPreset(const std::string &name) : name(name) {}

  CardPreset(const CardPreset &other) : preset(other.preset), name(other.name), number(other.number) {}

  int getLength() {
    return preset.size();
  }

  void setName(std::string name) {
    this->name = name;
  }

  std::string getName() {
    return name;
  }

  void addCard(Card &newCard) {
    newCard.setNumber(number);
    preset.push_back(newCard);
    number = ++number;
  }

  void removeCardByNumber(int &cardNumber) {
    int index = cardNumber - 1;
    if (index < preset.size()) {
      preset.erase(preset.begin() + index);

      for (int i = index; i < preset.size(); ++i) {
        preset[i].setNumber(preset[i].getNumber() - 1);
      }

    } else {
      std::cerr << "Index out of range" << std::endl;
    }
  }

  void shuffle() {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 g(rd()); // Seed the generator
    std::shuffle(preset.begin(), preset.end(), g);
  }

  Card &getCardByIndex(int &index) {
    return preset.at(index);
  }

  void clear() {
    preset.clear();
    number = 0;
  }

  std::string toJson() {
    Json::Value root;
    Json::StreamWriterBuilder builder;
    std::ostringstream os;

    root["presetName"] = this->name;

    Json::Value cards(Json::arrayValue);
    for (const auto &card : this->preset) {
      Json::Value cardJson;
      cardJson["title"] = card.title;
      cardJson["cardId"] = card.number;
      cardJson["description"] = card.text;
      cards.append(cardJson);
    }
    root["cards"] = cards;

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &os);
    return os.str();
  }

  const std::vector<Card> &getPreset() const {
    return preset;
  }
  const std::string &getName() const {
    return name;
  }
  int getNumber() const {
    return number;
  }

};

void init(Reminder::CardPreset &preset);

bool menu(bool &answer, bool flag);

void run(Reminder::CardPreset &preset);
}

#endif //REMINDER_GAMEPROCESS_H
