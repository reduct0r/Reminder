#include "GameProcess.h"
//TEST

namespace Reminder {
void init(Reminder::CardPreset &preset) {
  preset.shuffle();
}

bool menu(bool &answer, bool flag) {
  if (!flag) {
    std::cout << "1 - Right \t\t 0 - Wrong" << std::endl;
    std::cin >> answer;
    return answer;
  } else {
    std::cout << "1 - OK" << std::endl;
    std::cin >> answer;
    return answer;
  }
}

void run(Reminder::CardPreset &preset) {
  Reminder::CardPreset gamePreset(preset);

  init(gamePreset);

  bool answer = false;

  for (int i = 0; i < gamePreset.getLength(); ++i) {
    std::cout << gamePreset.getCardByIndex(i).getTitle() << std::endl;

    if (menu(answer, gamePreset.getCardByIndex(i).isFailed())) {
      gamePreset.getCardByIndex(i).setFailed(false);
      std::cout << gamePreset.getCardByIndex(i).getTitle() << " - ";
      std::cout << gamePreset.getCardByIndex(i).getText() << std::endl << std::endl;
    } else {
      gamePreset.getCardByIndex(i).setFailed(true);
      std::cout << "You are wrong" << std::endl << std::endl;
    }
  }

  for (int i = 0; i < gamePreset.getLength(); ++i) {
    if (gamePreset.getCardByIndex(i).isFailed()) {
      std::cout << gamePreset.getCardByIndex(i).getTitle() << " - ";
      std::cout << gamePreset.getCardByIndex(i).getText() << std::endl;

      if (menu(answer, gamePreset.getCardByIndex(i).isFailed())) {
        std::cout << "I hope you remember me now!" << std::endl << std::endl;
      } else {
        std::cerr << "Error ocurred :(" << std::endl << std::endl;
      }
    } else {
      continue;
    }
  }
}
}