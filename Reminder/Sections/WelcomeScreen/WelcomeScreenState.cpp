#include "WelcomeScreenState.h"
#include <iostream>
#include "WelcomeScreen.h"

WelcomeScreenState::WelcomeScreenState(sf::RenderWindow *window, std::stack<State *> *states, Settings &gfxSettings)
    : State(window, states), gfxSettings(gfxSettings) {
  this->InitTextures();
  this->InitVars();
  this->InitSprites();
  this->InitBG();
  this->InitFonts();
  this->InitButtons();
  this->InitTextBoxes();
}

WelcomeScreenState::~WelcomeScreenState() {
  auto it = this->buttons.begin();
  for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }

  auto it2 = this->textboxes.begin();
  for (auto it2 = this->textboxes.begin(); it2 != this->textboxes.end(); ++it2) {
    delete it2->second;
  }
}

void WelcomeScreenState::MoveSprites(float dir) {
  bool allSpritesAtTarget = true;

  for (auto &kv : this->targetPositions) {
    std::string key = kv.first;
    sf::Vector2f vector = kv.second * dir;

    sf::Vector2f startPos = this->startPositions[key];
    sf::Sprite &sprite = this->sprites[key];

    if (dir == -1) {
      startPos = sf::Vector2f(this->startPositions[key].x,
                              this->startPositions[key].y + this->distances[key] * this->targetPositions[key].y
                                  / abs(this->targetPositions[key].y));

      this->textboxes["LOGIN"]->setPosition(this->window->getSize().x * 10, 0);

      this->textboxes["PASSWORD"]->setPosition(this->window->getSize().x * 10, 0);

      this->buttons["BACK_BTN"]->Hide(1);

    }

    sf::Vector2f vectorBetweenPoints = sprite.getPosition() - startPos;
    float distanceS = std::hypot(vectorBetweenPoints.x, vectorBetweenPoints.y);

    if (distanceS <= this->distances[key]) {
      allSpritesAtTarget = false;

      sf::Vector2f direction = vector;
      float distance = this->distances[key];

      // Ускорение и замедление при движении
      float acceleration = 16 * this->scale * abs(distance - distanceS);
      if (acceleration < 5) {
        acceleration = 5;
      }
      float speed = acceleration * this->dt;

      if (distance > speed) {
        direction /= distance;
        sprite.move(direction * speed);
      } else {
        sprite.setPosition(vector);
      }
    }
  }

  if (allSpritesAtTarget) {
    this->animTransit = 0;
    this->animTransitReverse = 0;

    if (dir == 1) {
      this->textboxes["LOGIN"]->setPosition(
          this->sprites["LOG_FIELD"].getPosition().x + this->window->getSize().x / 20.0f,
          this->sprites["LOG_FIELD"].getPosition().y + this->window->getSize().y / 34.0f);
      this->textboxes["LOGIN"]->setSize(this->window->getSize().y / 2.1f, this->window->getSize().x / 40.0f);
      this->textboxes["LOGIN"]->SetColor(sf::Color(231, 240, 254, 255));

      this->textboxes["PASSWORD"]->setPosition(
          this->sprites["PASS_FIELD"].getPosition().x + this->window->getSize().x / 20.0f,
          this->sprites["PASS_FIELD"].getPosition().y + this->window->getSize().y / 34.0f);
      this->textboxes["PASSWORD"]->setSize(this->window->getSize().y / 2.1f, this->window->getSize().x / 40.0f);
      this->textboxes["PASSWORD"]->SetColor(sf::Color(231, 240, 254, 255));

      this->buttons["BACK_BTN"]->Hide(0);
    } else if (dir == -1) {
      for (auto &kv : this->startPositions) // избавляемся от погрешности
      {
        std::string key = kv.first;
        sf::Vector2f backP = kv.second;

        this->sprites[key].setPosition(backP);
      }
    }

  }
}

void WelcomeScreenState::UpdateKeyBoardBinds(const float &dt) {
  this->CheckForQuit();
}

void WelcomeScreenState::EndState() {
  std::cout << "Welcome Screen ENDING...";
}

void WelcomeScreenState::InitVars() {
  this->scale = static_cast<float>(this->window->getSize().x) / this->textures["BG_WELCOME"].getSize().x;
  std::cout << this->scale << "\n";
}

void WelcomeScreenState::InitBG() {
  float scale = this->scale;

  this->bg.setScale(sf::Vector2f(scale, scale));
  this->bg.setTexture(this->textures["BG_WELCOME"]);
}

void WelcomeScreenState::InitFonts() {
  if (!this->font.loadFromFile("Resources/Fonts/ARIAL.ttf")) {
    throw ("WelcomeScreenState: COULD NOT LOAD FONT");
  }
}

void WelcomeScreenState::InitButtons() {
  float winX = float(this->window->getSize().x);
  float winY = float(this->window->getSize().y);

  float scale = this->scale;
  float mid = winX / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().x * scale / 2.0;
  float yaw = winY / 2.0 - this->textures["LOGIN_BT_IDLE"].getSize().y * scale / 2.0;

  this->buttons["LOGIN_BTN"] = new ReminderUI::Button(mid,
                                                      yaw + winY / 6.0,
                                                      scale,
                                                      this->textures["LOGIN_BT_IDLE"],
                                                      this->textures["LOGIN_BT_HOVER"],
                                                      this->textures["LOGIN_BT_HOVER"]);

  this->buttons["REGISTER_BTN"] = new ReminderUI::Button(mid,
                                                         yaw + winY / 30.0f,
                                                         scale,
                                                         this->textures["REG_BT_IDLE"],
                                                         this->textures["REG_BT_HOVER"],
                                                         this->textures["REG_BT_HOVER"]);
  this->startPositions["REGISTER_BTN"] = this->buttons["REGISTER_BTN"]->getPos();

  this->buttons["GITHUB_BTN"] =
      new ReminderUI::Button(winX / 2.0 - this->textures["GITHUB_ICON"].getSize().x * scale / 2.0,
                             winY / 1.25,
                             scale,
                             this->textures["GITHUB_ICON"],
                             this->textures["GITHUB_ICON"],
                             this->textures["GITHUB_ICON"]);

  this->buttons["BACK_BTN"] = new ReminderUI::Button(winY / 18,
                                                     winY / 18,
                                                     scale,
                                                     this->textures["BACK"],
                                                     this->textures["BACK"],
                                                     this->textures["BACK"]);
  this->buttons["BACK_BTN"]->Hide(1);

}

void WelcomeScreenState::InitTextBoxes() {
  this->textboxes["LOGIN"] = new ReminderUI::TextBox(0, 0, 0, 0, 0);
  this->textboxes["PASSWORD"] = new ReminderUI::TextBox(0, 0, 0, 0, 0);
}

void WelcomeScreenState::InitTextures() {
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

void WelcomeScreenState::InitSprites() {
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
  sprite.setPosition(winX / 2.0 - this->textures["LOGO"].getSize().x * scale / 2.05,
                     winY / 2.0 - this->textures["LOGO"].getSize().y * scale / 2.0 - winY / 5.0);
  this->sprites["LOGO"] = sprite;
  this->targetPositions["LOGO"] = sf::Vector2f(0, this->window->getSize().y / -10.8);
  this->distances["LOGO"] = this->window->getSize().y / 15.5;
  this->startPositions["LOGO"] = sprite.getPosition();

}

// UPDATE
void WelcomeScreenState::Update(const float &dt) {
  this->UpdateDT();
  this->UpdateMousePos();
  this->UpdateKeyTime(dt);
  this->UpdateButtons();
  this->UpdateEvents();

  if (this->animTransit) {
    MoveSprites(1);
    this->buttons["REGISTER_BTN"]->moveA(this->scale,
                                         sf::Vector2f(0, this->window->getSize().y / 6.75),
                                         this->window->getSize().y / 6.75,
                                         this->startPositions["REGISTER_BTN"],
                                         1);
  }

  if (this->animTransitReverse) {
    MoveSprites(-1);
    this->buttons["REGISTER_BTN"]->moveA(this->scale,
                                         sf::Vector2f(0, this->window->getSize().y / 6.75),
                                         this->window->getSize().y / 6.75,
                                         this->startPositions["REGISTER_BTN"],
                                         -1);

  }

  if (this->bg.getTexture()->getSize().x * this->scale != this->window->getSize().x) {
    this->window->clear();
    if (this->gfxSettings.fullscreen) {

      this->window->create(this->gfxSettings.resolution,
                           this->gfxSettings.title,
                           sf::Style::Fullscreen,
                           this->gfxSettings.contextSettings);
    } else {
      this->window->create(this->gfxSettings.resolution,
                           this->gfxSettings.title,
                           sf::Style::Titlebar | sf::Style::Close,
                           this->gfxSettings.contextSettings);
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

void WelcomeScreenState::UpdateDT() {
  this->dt = this->dtClock.restart().asSeconds();
}

void WelcomeScreenState::UpdateButtons() {
  for (auto &it : this->buttons) {
    it.second->Update(this->MousePosView);
  }

  if (flag1 and this->buttons["LOGIN_BTN"]->isPressed() and !this->animTransit
      and !this->animTransitReverse) // первое нажатие на login
  {
    flag1 = 0;
    this->animTransit = 1;
    this->buttons["REGISTER_BTN"]->Hide(1);

//    this->states->push(new MainMenuState(this->window, this->states, this->gfxSettings)); // для отладки переход
  } else if (flag3 and this->buttons["LOGIN_BTN"]->isPressed() and !this->animTransitReverse and !this->animTransit
      and this->textboxes["LOGIN"]->getCurrentText() != ""
      and this->textboxes["PASSWORD"]->getCurrentText() != "") // второе нажатие на login, когда поля открыты
  {
    flag3 = 0;
    this->animTransit = 1;

    UserDAO userLogin(this->textboxes["LOGIN"]->getCurrentText(), this->textboxes["PASSWORD"]->getCurrentText());
    UserDAO existingUserLogin = database.getUser(userLogin);

    if (existingUserLogin.isEmpty()) {
      // TODO
      flag3 = 1;
    } else {
      this->states->push(new MainMenuState(this->window, this->states, this->gfxSettings));
      flag3 = 1;
    }
  }

  if (flag1 and this->buttons["REGISTER_BTN"]->isPressed() and this->getKeyTime() and !this->animTransit
      and !this->animTransitReverse) // первое нажатие на register
  {
    this->buttons["LOGIN_BTN"]->Hide(1);

    flag1 = 0;
    this->animTransit = 1;

  } else if (flag3 and this->buttons["REGISTER_BTN"]->isPressed() and !this->animTransitReverse
      and !this->animTransit // второе нажатие на register, когда поля открыты
      and this->textboxes["LOGIN"]->getCurrentText() != "" and this->textboxes["PASSWORD"]->getCurrentText() != "") {
    flag3 = 0;

    UserDAO user(this->textboxes["LOGIN"]->getCurrentText(),
                 this->textboxes["PASSWORD"]->getCurrentText());

    Reminder::Database database;
    UserDAO existingUser = database.createUser(user.getUsername(), user.getPassword());

    if (existingUser.isEmpty()) {
      flag3 = 1;
    } else {
      SessionIdService::saveNewSessionId(existingUser.getSessionId());
      this->states->push(new MainMenuState(this->window, this->states, this->gfxSettings));
      flag1 = 1;
    }
  }

  if (this->buttons["BACK_BTN"]->isPressed() and !this->animTransit and !this->animTransitReverse) {
    this->animTransitReverse = 1;
    this->buttons["LOGIN_BTN"]->Hide(0);
    this->buttons["REGISTER_BTN"]->Hide(0);
    flag1 = 1;
    flag3 = 1;
  }

  if (!flag2 and !this->animTransitReverse) {
    flag1 = 1;
    flag3 = 1;
  }

  if (this->buttons["GITHUB_BTN"]->isPressed() and this->getKeyTime()) {
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

void WelcomeScreenState::UpdateSprites() {

}

void WelcomeScreenState::UpdateEvents() {
  while (this->window->pollEvent(this->sfEvent)) {
    if (this->sfEvent.type == sf::Event::Closed) {
      this->window->close();
    }
    UpdateTextBoxesEvent();
  }
}

void WelcomeScreenState::UpdateTextBoxesEvent() {
  for (auto &it : this->textboxes) {
    it.second->handleEvent(this->sfEvent);
  }
}

//RENDER
void WelcomeScreenState::Render(sf::RenderTarget *target) {
  if (!target) {
    target = this->window;
  }

  target->draw(this->bg);
  this->RenderButtons(target);
  this->RenderSprites(target);
  this->RenderTextBoxes(target);
}

void WelcomeScreenState::RenderTextBoxes(sf::RenderTarget *target) {
  for (auto &it : this->textboxes) {
    it.second->Render(target);
  }
}

void WelcomeScreenState::RenderButtons(sf::RenderTarget *target) {
  for (auto &it : this->buttons) {
    it.second->Render(target);
  }
}

void WelcomeScreenState::RenderSprites(sf::RenderTarget *target) {
  for (auto &it : this->sprites) {
    target->draw(it.second);
  }
}