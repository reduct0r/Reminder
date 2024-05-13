#include "WelcomeScreen.h"
#include <iostream>

void WelcomeScreen::InitWindow()
{

    if (this->gfxSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
    }
    
    this->window->setFramerateLimit(this->gfxSettings.frameLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.VSync);
}

void WelcomeScreen::InitVars()
{
    this->window = nullptr;
    this->dt = 0;
}

void WelcomeScreen::InitStates()
{
    this->states.push(new WelcomeScreenState(this->window, &this->states, this->gfxSettings));
}

void WelcomeScreen::InitSettings()
{
    this->gfxSettings.LoadFromFile("Config/SFML SPECS.ini");

}

WelcomeScreen::WelcomeScreen()
{
    this->InitVars();
    this->InitSettings();
    this->InitWindow();
    this->InitStates();
}

WelcomeScreen::~WelcomeScreen()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// FUNCTIONS

void WelcomeScreen::Update()
{
    this->UpdateEvents();

    if (!this->states.empty())
    {
        this->states.top()->Update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->EndState();
            delete this->states.top();
            this->states.pop();
        }
    }

    else
    {
        this->EndApplication(); // ДЕЙСТВИЕ ПЕРЕД ВЫХОДОМ
        this->window->close();
    }
}


void WelcomeScreen::EndApplication()
{
    // ДЕЛАЕМ ВСЕ ЧТО НУЖНО ПЕРЕД ТЕМ КАК ЗАКРЫТЬ ОКНО
    std::cout << "EXIT";
}

void WelcomeScreen::Run()
{
    while (this->window->isOpen())
    {
        this->UpdateDT();
        this->Update();
        this->Render();
    }
}

void WelcomeScreen::UpdateEvents()
{

}

void WelcomeScreen::UpdateDT()
{
    this->dt = this->dtClock.restart().asSeconds();
}

// RENDER
void WelcomeScreen::Render()
{
    this->window->clear();

    if (!this->states.empty())
    {
        this->states.top()->Render(this->window);
    }

    this->window->display();
}

//void DemoCard(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs)
//{
//    sf::Sprite sprite(textureManager.getTexture("card1"));
//    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);     // Точка поворота в центр спрайта
//    sprite.setPosition(mainWindowSpecs.getWidth() / 2, mainWindowSpecs.getHeight() / 2);         // Позиционирование спрайта в центре окна
//
//    float scaleX = 0.5f; // Исходный масштаб по X и Y
//    const float scaleY = 0.5f;
//    sprite.setScale(scaleX, scaleY);
//
//    // Параметры для анимации сжатия и расширения (поворот)
//    bool squeezing = 1; // Направление изменения масштаба
//    bool changed = 0;   // Замена текстуры
//    while (mainWindow.isOpen())
//    {
//        sf::Event event;
//        while (mainWindow.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                mainWindow.close();
//        }
//        if (squeezing)
//        {
//            scaleX -= 0.01;
//        }
//        else
//        {
//            scaleX += 0.01;
//        }
//
//        if (scaleX <= 0 or scaleX >= 0.5)         // Изменение направления анимации и текстуры при достижении границ   
//        {
//            if (scaleX <= 0 and changed == 0)
//            {
//                sprite.setTexture(textureManager.getTexture("card2"));
//                changed = 1;
//            }
//
//            else if (scaleX <= 0 and changed == 1)
//            {
//                sprite.setTexture(textureManager.getTexture("card1"));
//                changed = 0;
//            }
//
//            squeezing = !squeezing;
//        }
//
//        sprite.setScale(scaleX, scaleY);
//
//        mainWindow.clear();
//        mainWindow.draw(sprite);
//        mainWindow.display();
//    }
//
//}
