#include "Sections/WelcomeScreen/H_Welcome_screen.h"
#include "Database/Database.h"

int main() {

  Reminder::Database database;

  std::cout << database.addUser("Exist", "admin") << std::endl;

  std::cout << database.getPassword("Exist") << std::endl;

  // ShowWelcomeScreen();

  return 0;
}
