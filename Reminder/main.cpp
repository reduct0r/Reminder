#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Sections/WelcomeScreen/H_Welcome_screen.h"
#include "Database/Database.h"

int main() {


  Database database;

  // database.initDatabase();

  ShowWelcomeScreen();

  return 0;
}