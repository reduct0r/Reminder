#include "WelcomeScreenState.h"
#include <iostream>
#include "WelcomeScreen.h"

WelcomeScreenState::WelcomeScreenState(sf::RenderWindow* window, std::stack<State*>* states, Settings& gfxSettings)
	:State(window, states), gfxSettings(gfxSettings)
{
	this->InitTextures();
	this->InitVars();
	this->InitSprites();
	this->InitBG();
	this->InitFonts();
	this->InitButtons();
	this->InitTextBoxes();
}

WelcomeScreenState::~WelcomeScreenState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->textboxes.begin();
	for (auto it2 = this->textboxes.begin(); it2 != this->textboxes.end(); ++it2)
	{
		delete it2->second;
	}
}

void WelcomeScreenState::MoveSprites(float dir)
{
	bool allSpritesAtTarget = true;

	for (auto& kv : this->targetPositions)
	{
		std::string key = kv.first;
		sf::Vector2f vector = kv.second * dir;

		sf::Vector2f startPos = this->startPositions[key];
		sf::Sprite& sprite = this->sprites[key];

		if (dir == -1)
		{
			startPos = sf::Vector2f(this->startPositions[key].x,
				this->startPositions[key].y + this->distances[key] * this->targetPositions[key].y / abs(this->targetPositions[key].y));

			this->textboxes["LOGIN"]->setPosition(this->window->getSize().x * 10, 0);

			this->textboxes["PASSWORD"]->setPosition(this->window->getSize().x * 10, 0);

			this->buttons["BACK_BTN"]->Hide(1, this->scale);

		}

		sf::Vector2f vectorBetweenPoints = sprite.getPosition() - startPos;
		float distanceS = std::hypot(vectorBetweenPoints.x, vectorBetweenPoints.y);

		if (distanceS <= this->distances[key])
		{
			allSpritesAtTarget = false;

			sf::Vector2f direction = vector;
			float distance = this->distances[key];

			// Ускорение и замедление при движении
			float acceleration = 16 * this->scale * abs(distance - distanceS);
			if (acceleration < 5)
			{
				acceleration = 5;
			}
			float speed = acceleration * this->dt;

			if (distance > speed)
			{
				direction /= distance;
				sprite.move(direction * speed);
			}
			else
			{
				sprite.setPosition(vector);
			}
		}
	}

	if (allSpritesAtTarget)
	{
		this->animTransit = 0;
		this->animTransitReverse = 0;

		if (dir == 1)
		{
			this->textboxes["LOGIN"]->setPosition(this->sprites["LOG_FIELD"].getPosition().x + this->window->getSize().x / 20.0f,
				this->sprites["LOG_FIELD"].getPosition().y + this->window->getSize().y / 34.0f);
			this->textboxes["LOGIN"]->setSize(this->window->getSize().y / 2.1f, this->window->getSize().x / 40.0f);
			this->textboxes["LOGIN"]->SetColor(sf::Color(231, 240, 254, 255));

			this->textboxes["PASSWORD"]->setPosition(this->sprites["PASS_FIELD"].getPosition().x + this->window->getSize().x / 20.0f,
				this->sprites["PASS_FIELD"].getPosition().y + this->window->getSize().y / 34.0f);
			this->textboxes["PASSWORD"]->setSize(this->window->getSize().y / 2.1f, this->window->getSize().x / 40.0f);
			this->textboxes["PASSWORD"]->SetColor(sf::Color(231, 240, 254, 255));

			this->buttons["BACK_BTN"]->Hide(0, this->scale);
		}

		else if (dir == -1)
		{
			for (auto& kv : this->startPositions) // избавляемся от погрешности
			{
				std::string key = kv.first;
				sf::Vector2f backP = kv.second;

				this->sprites[key].setPosition(backP);
			}
		}

	}
}

//bool WelcomeScreenState::moveA(sf::Sprite& sprite, float VelX, float VelY, float distance) const
//{
//	static float accumulatedDistance = 0.0f; // Аккумулированное расстояние перемещения
//	static bool init = true; // Переменная для инициализации или перезапуска анимации
//	static bool init2 = 0; // Переменная для инициализации или перезапуска анимации
//	static sf::Vector2f initialPos; // Начальная позиция кнопки
//
//	// Сохраняем начальное состояние и расположение
//	if (init and VelY > 0)
//	{
//		initialPos = sprite.getPosition();
//		accumulatedDistance = 0.0f;
//		init = false;
//	}
//
//	if (init2 and VelY < 0)
//	{
//		initialPos = sprite.getPosition();
//		accumulatedDistance = 0.0f;
//		init2 = false;
//	}
//
//	// Вычисляем необходимое смещение за текущий кадр
//	float moveX = VelX * this->dt;
//	float moveY = VelY * this->dt;
//	float frameDistance = std::sqrt(moveX * moveX + moveY * moveY); // Расстояние, пройденное за фрейм
//
//	// Проверяем, не превысили ли мы общее расстояние
//	if (accumulatedDistance + frameDistance >= distance and distance > 0)
//	{
//		init2 = true; // Сбрасываем статус для новых вызовов анимации
//		return 1;
//	}
//
//	else if (accumulatedDistance + frameDistance <= distance and distance < 0)
//	{
//		init = true; // Сбрасываем статус для новых вызовов анимации
//		return 1;
//	}
//
//	else
//	{
//		sprite.move(moveX, moveY); // Перемещаем кнопку
//		accumulatedDistance += frameDistance; // Обновляем накопленное расстояние
//	}
//	return 0;
//}
//
//void WelcomeScreenState::AnimOpenFields()
//{
//	/* REG BUTTON */
//	static float speed, speed1, speed2, speed3;
// 	static float acceleration = this->scale / 2.0f;
//
//	float a = acceleration;
//	static float startPos = this->buttons["REGISTER_BTN"]->getPos().x;
//	static float duration = -this->scale * 20;
//	static bool isLoginBtnHidden = false;
//	if (!isLoginBtnHidden)
//	{
//		this->sprites["LOG_FIELD"].setScale(scale, scale);
//		this->sprites["PASS_FIELD"].setScale(scale, scale);
//		speed = this->scale * 2;
//		speed1 = this->scale *0;
//		speed2 = this->scale * 0;
//		speed3 = this->scale * 0;
//		this->buttons["LOGIN_BTN"]->Hide(1, this->scale);
//		this->buttons["BACK_BTN"]->Hide(0, this->scale);
//		isLoginBtnHidden = true;
//	}
//
//
//	/* кнопка регистрации */
//
//	//if (this->buttons["REGISTER_BTN"]->move(0, 1000, 4*this->scale))
//	//{
//	//	speed = 0;
//	//}
//
//	////sf::Vector2f posB = this->buttons["REGISTER_BTN"]->getPos();
//
//	////if (posB.y - startPos >= duration)
//	////{
//	////	a = -acceleration;
//	////}
//	////if (speed <= 0)
//	////{
//	////	a = 0;
//	////	speed = 0;
//	////}
//
//	////speed += a;
//	////this->buttons["REGISTER_BTN"]->setPos(posB.x, posB.y + speed);
//
//
//	///* FIELDS */
//
//	if (moveA(this->sprites["LOG_FIELD"], 0, 100, 100))
//	{
//		speed = 0;
//	}
//
//
//
//
//
//	///*float scale = this->scale;
//	//
//	//float a1 = acceleration;
//	//static float startPos1 = sprites["LOG_FIELD"].getPosition().y;
//	//static float duration1 = this->scale * 70;
//	//sf::Vector2f posF1 = this->sprites["LOG_FIELD"].getPosition();
//	//if (posF1.y - startPos1 >= duration1)
//	//{
//	//	a1 = -acceleration;
//	//}
//	//if (speed1 <= 0)
//	//{
//	//	a1 = 0;
//	//	speed1 = 0;
//	//}
//	//speed1 += a1;
//	//this->sprites["LOG_FIELD"].setPosition(posF1.x, posF1.y + speed1);*/
//
//
//	//if (moveA(this->sprites["PASS_FIELD"], 0, 1000, 7 * this->scale))
//	//{
//	//	speed2 = 0;
//	//}
//
//
//
//	////sf::Vector2f posF2 = this->sprites["PASS_FIELD"].getPosition();
//	////static float duration2 = this->scale * 130;
//	////static float startPos2 = sprites["PASS_FIELD"].getPosition().y;
//	////float a2 = acceleration;
//
//	////if (posF2.y - startPos2 >= duration2)
//	////{
//	////	a2 = -acceleration;
//	////}
//	////if (speed2 <= 0)
//	////{
//	////	a2 = 0;
//	////	speed2 = 0;
//	////}
//	////speed2 += a2;
//	////this->sprites["PASS_FIELD"].setPosition(posF2.x, posF2.y + speed2);
//
//
//	//if (moveA(this->sprites["PASS_FIELD"], 0, 1000, 7 * this->scale))
//	//{
//	//	speed3 = 0;
//	//}
//
//	///* logo */
//	////static float startPos3 = sprites["LOGO"].getPosition().y;
//	////static float duration3 = this->scale * 60;
//	////sf::Vector2f posF3 = this->sprites["LOGO"].getPosition();
//
//	////if (startPos3 - posF3.y >= duration3)
//	////{
//	////	speed3 = 0;
//	////}
//	////this->sprites["LOGO"].setPosition(posF3.x, posF3.y - speed3);
//
//
//
//	if (speed == 0 and speed1 == 0 and speed2 == 0 and speed3 == 0)
//	{
//		this->textboxes["LOGIN"]->setPosition(this->sprites["LOG_FIELD"].getPosition().x + this->window->getSize().x / 20.0f, 
//			this->sprites["LOG_FIELD"].getPosition().y + this->window->getSize().y / 34.0f);
//		this->textboxes["LOGIN"]->setSize(this->window->getSize().y / 2.1f, this->window->getSize().x / 40.0f);
//		this->textboxes["LOGIN"]->SetColor(sf::Color::Color(231, 240, 254, 255));
//
//		this->textboxes["PASSWORD"]->setPosition(this->sprites["PASS_FIELD"].getPosition().x + this->window->getSize().x / 20.0f,
//			this->sprites["PASS_FIELD"].getPosition().y + this->window->getSize().y / 34.0f);
//		this->textboxes["PASSWORD"]->setSize(this->window->getSize().y / 2.1f, this->window->getSize().x / 40.0f);
//		this->textboxes["PASSWORD"]->SetColor(sf::Color::Color(231, 240, 254, 255));
//		
//		this->animTransit = 0;
//		std::cout << "clown";
//		isLoginBtnHidden = 0;
//	}
//}
//




//
//
//
//void WelcomeScreenState::AnimCloseFields()
//{
//	/* REG BUTTON */
//	static float speed, speed1, speed2, speed3;
//	static float acceleration = this->scale / 2.0f;
//
//	float a = acceleration;
//	static float startPos = this->buttons["REGISTER_BTN"]->getPos().x;
//	static float duration = this->scale * 10;
//	static bool isLoginBtnHidden = false;
//	if (!isLoginBtnHidden)
//	{
//		this->textboxes["LOGIN"]->setPosition(this->window->getSize().x, this->window->getSize().x);
//		this->textboxes["PASSWORD"]->setPosition(this->window->getSize().x, this->window->getSize().x);
//
//		speed = this->scale * 2;
//		speed1 = this->scale;
//		speed2 = this->scale * 1.4;
//		speed3 = this->scale * 1.6;
//		this->buttons["LOGIN_BTN"]->Hide(0, this->scale);
//		this->buttons["BACK_BTN"]->Hide(1, this->scale);
//		isLoginBtnHidden = true;
//	}
//
//	if (this->buttons["REGISTER_BTN"]->move(0, 1000, -4 * this->scale))
//	{
//		speed = 0;
//	}
//
//
//	/*sf::Vector2f posB = this->buttons["REGISTER_BTN"]->getPos();
//
//	
//	if (startPos - posB.y >= duration)
//	{
//		a = -acceleration;
//	}
//	if (speed <= 0)
//	{
//		a = 0;
//		speed = 0;
//	}
//	speed += a;
//	this->buttons["REGISTER_BTN"]->setPos(posB.x, posB.y - speed);*/
//
//	/* FIELDS */
//	float scale = this->scale;
//	float a1 = acceleration;
//	static float startPos1 = sprites["LOG_FIELD"].getPosition().y;
//	static float duration1 = this->scale * 70;
//
//
//	if (moveA(sprites["LOG_FIELD"], 0, -100, 100))
//	{
//		speed1 = 0;
//	}
//
//	/*sf::Vector2f posF1 = this->sprites["LOG_FIELD"].getPosition();
//	if (startPos1 - posF1.y >= duration1)
//	{
//		a1 = -acceleration;
//	}
//	if (speed1 <= 0)
//	{
//		a1 = 0;
//		speed1 = 0;
//	}
//	speed1 += a1;
//	this->sprites["LOG_FIELD"].setPosition(posF1.x, posF1.y - speed1);*/
//
//
//	sf::Vector2f posF2 = this->sprites["PASS_FIELD"].getPosition();
//	static float duration2 = this->scale * 130;
//	static float startPos2 = sprites["PASS_FIELD"].getPosition().y;
//	float a2 = acceleration;
//
//	if (startPos2 - posF2.y >= duration2)
//	{
//		a2 = -acceleration;
//	}
//	if (speed2 <= 0)
//	{
//		a2 = 0;
//		speed2 = 0;
//	}
//	speed2 += a2;
//	this->sprites["PASS_FIELD"].setPosition(posF2.x, posF2.y - speed2);
//
//	/* logo */
//	static float startPos3 = sprites["LOGO"].getPosition().y;
//	static float duration3 = this->scale * 60;
//	sf::Vector2f posF3 = this->sprites["LOGO"].getPosition();
//
//	if (posF3.y - startPos3 >= duration3)
//	{
//		speed3 = 0;
//	}
//	this->sprites["LOGO"].setPosition(posF3.x, posF3.y + speed3);
//
//	if (speed == 0 and speed1 == 0 and speed2 == 0 and speed3 == 0)
//	{
//		this->animTransitReverse = 0;
//		isLoginBtnHidden = 0;
//	}
//}


void WelcomeScreenState::UpdateKeyBoardBinds(const float& dt)
{
	this->CheckForQuit();
}

void WelcomeScreenState::EndState()
{
	std::cout << "Welcome Screen ENDING...";
}


void WelcomeScreenState::InitVars()
{
	this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_WELCOME"].getSize().x;
	std::cout << this->scale << "\n";
}

void WelcomeScreenState::InitBG()
{
	float scale = this->scale;

	this->bg.setScale(sf::Vector2f(scale, scale));
	this->bg.setTexture(this->textures["BG_WELCOME"]);
}

void WelcomeScreenState::InitFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf"))
	{
		throw("WelcomeScreenState: COULD NOT LOAD FONT");
	}
}

void WelcomeScreenState::InitButtons()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);

	float scale = this->scale;
	float mid = winX / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().x * scale / 2.0;
	float yaw = winY / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().y * scale / 2.0;

	this->buttons["LOGIN_BTN"] = new  ReminderUI::Button(mid, yaw + winY / 6.0, scale, scale, &this->font, sf::String(""), this->textures["LOGIN_BT_IDLE"], this->textures["LOGIN_BT_HOVER"], this->textures["LOGIN_BT_HOVER"]);

	this->buttons["REGISTER_BTN"] = new  ReminderUI::Button(mid, yaw + winY / 30.0f, scale, scale, &this->font, sf::String(""), this->textures["REG_BT_IDLE"], this->textures["REG_BT_HOVER"], this->textures["REG_BT_HOVER"]);
	this->startPositions["REGISTER_BTN"] = this->buttons["REGISTER_BTN"]->getPos();

	this->buttons["GITHUB_BTN"] = new  ReminderUI::Button(winX / 2.0 - this->textures["GITHUB_ICON"].getSize().x * scale / 2.0, winY / 1.25, scale, scale, &this->font, sf::String(""), this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"], this->textures["GITHUB_ICON"]);

	this->buttons["BACK_BTN"] = new  ReminderUI::Button(30, 30, scale, scale, &this->font, sf::String(""), this->textures["BACK"], this->textures["BACK"], this->textures["BACK"]);
	this->buttons["BACK_BTN"]->Hide(1, this->scale);

}

void WelcomeScreenState::InitTextBoxes()
{
	this->textboxes["LOGIN"] = new ReminderUI::TextBox(0, 0, 0, 0, 0);
	this->textboxes["PASSWORD"] = new  ReminderUI::TextBox(0, 0, 0, 0, 0);
}

void WelcomeScreenState::InitTextures()
{
	sf::Texture texture;
	texture.setSmooth(1);
	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Background.png");
	this->textures["BG_WELCOME"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button first.png");
	this->textures["LOGIN_BT_IDLE"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Login button second.png");
	this->textures["LOGIN_BT_HOVER"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Reg button first.png");
	this->textures["REG_BT_IDLE"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Reg button second.png");
	this->textures["REG_BT_HOVER"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Github icon.png");
	this->textures["GITHUB_ICON"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/Logo reminder.png");
	this->textures["LOGO"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/login.png");
	this->textures["LOGIN_FIELD"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/password.png");
	this->textures["PASSWORD_FIELD"] = texture;

	texture.loadFromFile("Resources/Textures/UI/Welcome Screen/back2.png");
	this->textures["BACK"] = texture;

}

void WelcomeScreenState::InitSprites()
{
	float winX = float(this->window->getSize().x);
	float winY = float(this->window->getSize().y);
	float scale = this->scale;

	sf::Sprite sprite1;
	sprite1.setScale(scale, scale);
	sprite1.setTexture(this->textures["LOGIN_FIELD"]);
	sprite1.setPosition(winX / 2.0 - this->textures["LOGIN_FIELD"].getSize().x * scale / 2.0, winY / 4.0);
	this->sprites["LOG_FIELD"] = sprite1;
	this->targetPositions["LOG_FIELD"] = sf::Vector2f(0, this->window->getSize().y / 6.75);
	this->distances["LOG_FIELD"] = this->window->getSize().y / 7.7;
	this->startPositions["LOG_FIELD"] = sprite1.getPosition();

	sf::Sprite sprite3;
	sprite3.setScale(scale, scale);
	sprite3.setTexture(this->textures["PASSWORD_FIELD"]);
	sprite3.setPosition(winX / 2.0 - this->textures["PASSWORD_FIELD"].getSize().x * scale / 2.0, winY / 4.0);
	this->sprites["PASS_FIELD"] = sprite3;
	this->targetPositions["PASS_FIELD"] = sf::Vector2f(0, this->window->getSize().y / 5.4);
	this->distances["PASS_FIELD"] = this->window->getSize().y / 4.15;
	this->startPositions["PASS_FIELD"] = sprite3.getPosition();

	sf::Sprite sprite;
	sprite.setScale(scale, scale);
	sprite.setTexture(this->textures["LOGO"]);
	sprite.setPosition(winX / 2.0 - this->textures["LOGO"].getSize().x * scale / 2.05, winY / 2.0 - this->textures["LOGO"].getSize().y * scale / 2.0 - winY / 5.0);
	this->sprites["LOGO"] = sprite;
	this->targetPositions["LOGO"] = sf::Vector2f(0, this->window->getSize().y / -10.8);
	this->distances["LOGO"] = this->window->getSize().y / 15.5;
	this->startPositions["LOGO"] = sprite.getPosition();


}

// UPDATE 
void WelcomeScreenState::Update(const float& dt)
{
	this->UpdateDT();
	this->UpdateMousePos();
	this->UpdateKeyTime(dt);
	this->UpdateButtons();
	this->UpdateEvents();

	if (this->animTransit)
	{
		MoveSprites(1);
		this->buttons["REGISTER_BTN"]->moveA(this->scale, sf::Vector2f(0, this->window->getSize().y / 6.75), this->window->getSize().y / 6.75, this->startPositions["REGISTER_BTN"], 1);

		//AnimOpenFields();
	}

	if (this->animTransitReverse)
	{
		MoveSprites(-1);
		this->buttons["REGISTER_BTN"]->moveA(this->scale, sf::Vector2f(0, this->window->getSize().y / 6.75), this->window->getSize().y / 6.75, this->startPositions["REGISTER_BTN"], -1);

	}
	//if (this->animTransitReverse and !this->animTransit)
	//{
	//	AnimCloseFields();
	//}

	if (this->bg.getTexture()->getSize().x * this->scale != this->window->getSize().x)
	{
		this->window->clear();
		if (this->gfxSettings.fullscreen)
		{

			this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);
		}
		else
		{
			this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
		}

		this->window->setFramerateLimit(this->gfxSettings.frameLimit);
		this->window->setVerticalSyncEnabled(this->gfxSettings.VSync);

		this->buttons.clear();
		this->textboxes.clear();


		this->InitTextures();
		this->InitVars();
		this->InitSprites();
		this->InitBG();
		this->InitFonts();
		this->InitButtons();
		this->InitTextBoxes();
	}
}

void WelcomeScreenState::UpdateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void WelcomeScreenState::UpdateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->MousePosView);
	}

	/* Обработка кнопок */
	static bool flag1 = true;
	static bool flag2 = true;
	static bool flag3 = true;

	if (flag1 and this->buttons["LOGIN_BTN"]->isPressed()) // первое нажатие на login
	{
		flag1 = 0;
		this->animTransit = 1;
		this->buttons["REGISTER_BTN"]->Hide(1, this->scale);
		//this->states->push(new MainMenuState(this->window, this->states, this->gfxSettings));
	}

	else if (flag3 and this->buttons["LOGIN_BTN"]->isPressed() and !this->animTransitReverse and !this->animTransit
		and this->textboxes["LOGIN"]->getCurrentText() != "" and this->textboxes["PASSWORD"]->getCurrentText() != "") // второе нажатие на login, когда поля открыты
	{
		flag3 = 0;
		this->animTransit = 1;
		std::cout << "READY";
	}

	if (flag1 and this->buttons["REGISTER_BTN"]->isPressed() and this->getKeyTime()) // первое нажатие на register
	{
		this->buttons["LOGIN_BTN"]->Hide(1, this->scale);

		flag1 = 0;
		this->animTransit = 1;

	}

	else if (flag3 and this->buttons["REGISTER_BTN"]->isPressed() and !this->animTransitReverse and !this->animTransit // второе нажатие на register, когда поля открыты
		and this->textboxes["LOGIN"]->getCurrentText() != "" and this->textboxes["PASSWORD"]->getCurrentText() != "") {
		flag3 = 0;

		UserDAO user(this->textboxes["LOGIN"]->getCurrentText(),
			this->textboxes["PASSWORD"]->getCurrentText());

		Reminder::Database database;
		UserDAO existingUser = database.createUser(user.GetUsername(), user.GetPassword());

		if (existingUser.isEmpty()) {
			// TODO
			// Ð Ð°Ð¼ÐºÐ° Ð² ÐºÑÐ°ÑÐ½ÑÐ¹ ÑÐ²ÐµÑ Ð¸Ð»Ð¸ Ð¾ÑÐºÑÑÑÐ¸Ðµ Ð¾ÐºÐ½Ð° Ð»Ð¾Ð³Ð¸Ð½Ð° фикси кодировку
		}
		else {
			SessionIdService::saveStringToLocal(existingUser.GetSessionId());
			this->states->push(new MainMenuState(this->window, this->states, this->gfxSettings));
		}
	}

	if (this->buttons["BACK_BTN"]->isPressed() and !this->animTransit and !this->animTransitReverse)
	{
		this->animTransitReverse = 1;
		this->buttons["LOGIN_BTN"]->Hide(0, this->scale);
		this->buttons["REGISTER_BTN"]->Hide(0, this->scale);
		flag1 = 1;
		flag3 = 1;

	}

	if (!flag2 and !this->animTransitReverse)
	{
		flag1 = 1;
		flag3 = 1;
	}

	if (this->buttons["GITHUB_BTN"]->isPressed() and this->getKeyTime())
	{
		std::string url = "https://github.com/reduct0r/Reminder";

#ifdef _WIN32
		std::string command = "start " + url + ""; // Для Windows
#elif __APPLE__
		std::string command = "open " + url + ""; // Для macOS
#endif

		// Вызываем командную строку сформированной команды
		system(command.c_str());
	}
}

void WelcomeScreenState::UpdateSprites()
{

}

void WelcomeScreenState::UpdateEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
		UpdateTextBoxesEvent();
	}
}

void WelcomeScreenState::UpdateTextBoxesEvent()
{
	for (auto& it : this->textboxes)
	{
		it.second->handleEvent(this->sfEvent);
	}
}

//RENDER
void WelcomeScreenState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->bg);
	this->RenderButtons(target);
	this->RenderSprites(target);
	this->RenderTextBoxes(target);
}

void WelcomeScreenState::RenderTextBoxes(sf::RenderTarget* target)
{
	for (auto& it : this->textboxes)
	{
		it.second->Render(target);
	}
}

void WelcomeScreenState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void WelcomeScreenState::RenderSprites(sf::RenderTarget* target)
{
	for (auto& it : this->sprites)
	{
		target->draw(it.second);
	}
}
