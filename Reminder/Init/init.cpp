#include "H_Init.h"

Reminder::TextureManager Reminder::InitTexturesWelcome() {
  Reminder::TextureManager textureManager;
  textureManager.loadTexture("card1", "Resources/Textures/test_cards/card.jpg");
  textureManager.loadTexture("card2", "Resources/Textures/test_cards/card2.jpg");

  textureManager.loadTexture("Background_Main", "Resources/Textures/ReminderUI/Welcome Screen/Background.png");
  textureManager.loadTexture("Github_icon", "Resources/Textures/ReminderUI/Welcome Screen/Github icon.png");
  textureManager.loadTexture("Login_button", "Resources/Textures/ReminderUI/Welcome Screen/Login button first.png");
  textureManager.loadTexture("Login_button_hovered",
                             "Resources/Textures/ReminderUI/Welcome Screen/Login button second.png");

  textureManager.loadTexture("Reg_button", "Resources/Textures/ReminderUI/Welcome Screen/Reg button first.png");
  textureManager.loadTexture("Reg_button_hovered",
                             "Resources/Textures/ReminderUI/Welcome Screen/Reg button second.png");

  textureManager.loadTexture("logo", "Resources/Textures/ReminderUI/Welcome Screen/Logo reminder.png");

  textureManager.loadTexture("login_field", "Resources/Textures/ReminderUI/Welcome Screen/login.png");
  textureManager.loadTexture("passw_field", "Resources/Textures/ReminderUI/Welcome Screen/password.png");

  textureManager.loadTexture("back", "Resources/Textures/ReminderUI/Welcome Screen/back.png");

  return textureManager;
}

Reminder::TextureManager Reminder::InitTexturesMain() {
  Reminder::TextureManager textureManager;

  textureManager.loadTexture("Background_Main", "Resources/Textures/ReminderUI/Welcome Screen/Background.png");
  textureManager.loadTexture("LogOut", "Resources/Textures/ReminderUI/Main Menu/logout.png");

  return textureManager;
}