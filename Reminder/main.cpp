#include "Sections/Main menu/MainMenu.h"
#include "Sections/WelcomeScreen/WelcomeScreen.h"
#include "UI/MultilineTextBox.hpp"

int main() {

//  Reminder::Database database;

 // if (database.containsSessionId(SessionIdService::readSessionId()).isEmpty()) {
    WelcomeScreen welcomeScreen;
    welcomeScreen.Run();
  //} else {
  //  MainMenu mainMenu;
  //  mainMenu.Run();
 // }

  return 0;
}

//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML TextBox Example");
//    sf::Font font;
//    font.loadFromFile("Resources/Fonts/ARIAL.TTF");
//
//    MultiLineTextBox textBox(100, 100, 600, 400, font, 24);
//
//    sf::Clock clock;
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            textBox.handleEvent(event);
//        }
//
//        float deltaTime = clock.restart().asSeconds();
//        textBox.update(deltaTime);
//
//        window.clear();
//        textBox.draw(window);
//        window.display();
//    }
//
//    return 0;
//}


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

