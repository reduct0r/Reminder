#include "Sections/WelcomeScreen/H_Welcome_screen.h"
#include "Database/Database.h"

static Reminder::Database database;

void addUser() {
  std::string username;
  std::string password;

  std::cout << "Придумайте имя пользователя: ";
  std::cin >> username;
  std::cout << "Придумайте пароль для пользователя " + username + ": ";
  std::cin >> password;

  std::cout << database.addUser(username, password) << std::endl;
}

void checkPass() {
  std::string loginPassword;
  std::string username;

  std::cout << "Введите имя пользователя: ";
  std::cin >> username;
  std::cout << "Введите пароль для пользователя: " + username + ": ";
  std::cin >> loginPassword;

  if (Reminder::Database::comparePasswords(loginPassword, database.getPassword(username))) {
    std::cout << "Вы успешно вошли в аккаунт!\n";
  } else {
    std::cout << "Неверные данные!\n";
  }
}

int main() {
  while (true) {
    int activity;

    std::cout
        << "\t\t\t\tВыберите действие\n"
           "1 - Добавить пользователя\t\t2 - Войти в аккаунт"
           "\n\t\t\t3 - Выйти из программы\n";

    std::cin >> activity;

    switch (activity) {
      case 1:addUser();
        break;
      case 2:checkPass();
        break;
      case 3:return 0;
      default:std::cout << "Неверное действие!\n";
        break;
    }
  }
  // ShowWelcomeScreen();
}