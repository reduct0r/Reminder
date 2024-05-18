//#include "Sections/WelcomeScreen/H_Welcome_screen.h"
//#include <pqxx/pqxx>
#include "Sections/Main menu/MainMenu.h"
#include "Sections/WelcomeScreen/WelcomeScreen.h"

int main() {

  Reminder::Database database;

  if (database.containsSessionId(SessionIdService::readSessionId()).isEmpty()) {
    WelcomeScreen welcomeScreen;
    welcomeScreen.Run();
  } else {
    MainMenu mainMenu;
    mainMenu.Run();
  }




  return 0;
}

//
//#include "tinyfiledialogs.h"
//
//int main() {
//    // Открыть диалоговое окно выбора файла
//    const char* filePath = tinyfd_openFileDialog("Choose an image", "", 0, nullptr, nullptr, 0);
//
//    if (filePath != nullptr) {
//        // Load the image from file, create texture and sprite
//        sf::Texture texture;
//        if (texture.loadFromFile(filePath)) {
//            sf::Sprite sprite;
//            sprite.setTexture(texture);
//
//            // Render sprite as background or do something else with it
//        }
//    }
//
//    return 0;
//}
