#include "H_Init.h"

Reminder::TextureManager Reminder::InitTexturesMain()
{
	Reminder::TextureManager textureManagerMain;
	textureManagerMain.loadTexture("card1", "Resources/Textures/test_cards/card.jpg");
	textureManagerMain.loadTexture("card2", "Resources/Textures/test_cards/card2.jpg");

	textureManagerMain.loadTexture("Background_Main", "Resources/Textures/UI/Welcome Screen/Background.png");
	textureManagerMain.loadTexture("Github_icon", "Resources/Textures/UI/Welcome Screen/Github icon.png");
	textureManagerMain.loadTexture("Login_button", "Resources/Textures/UI/Welcome Screen/Login button first.png");
	textureManagerMain.loadTexture("Login_button_hovered", "Resources/Textures/UI/Welcome Screen/Login button second.png");

	textureManagerMain.loadTexture("Reg_button", "Resources/Textures/UI/Welcome Screen/Reg button first.png");
	textureManagerMain.loadTexture("Reg_button_hovered", "Resources/Textures/UI/Welcome Screen/Reg button second.png");

	return textureManagerMain;
}