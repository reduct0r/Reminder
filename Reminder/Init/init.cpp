#include "H_Init.h"

Reminder::TextureManager Reminder::InitTexturesWelcome()
{
	Reminder::TextureManager textureManager;
	textureManager.loadTexture("card1", "Resources/Textures/test_cards/card.jpg");
	textureManager.loadTexture("card2", "Resources/Textures/test_cards/card2.jpg");

	textureManager.loadTexture("Background_Main", "Resources/Textures/UI/Welcome Screen/Background.png");
	textureManager.loadTexture("Github_icon", "Resources/Textures/UI/Welcome Screen/Github icon.png");
	textureManager.loadTexture("Login_button", "Resources/Textures/UI/Welcome Screen/Login button first.png");
	textureManager.loadTexture("Login_button_hovered", "Resources/Textures/UI/Welcome Screen/Login button second.png");

	textureManager.loadTexture("Reg_button", "Resources/Textures/UI/Welcome Screen/Reg button first.png");
	textureManager.loadTexture("Reg_button_hovered", "Resources/Textures/UI/Welcome Screen/Reg button second.png");

	textureManager.loadTexture("logo", "Resources/Textures/UI/Welcome Screen/Logo reminder.png");

	textureManager.loadTexture("login_field", "Resources/Textures/UI/Welcome Screen/login.png");
	textureManager.loadTexture("passw_field", "Resources/Textures/UI/Welcome Screen/password.png");


	return textureManager;
}

Reminder::TextureManager Reminder::InitTexturesMain()
{
	Reminder::TextureManager textureManager;

	textureManager.loadTexture("Background_Main", "Resources/Textures/UI/Welcome Screen/Background.png");

	return textureManager;
}