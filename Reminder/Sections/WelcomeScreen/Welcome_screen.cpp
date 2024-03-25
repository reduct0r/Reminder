#include "H_Welcome_screen.h"

void ShowWelcomeScreen()
{
    Reminder::WindowSpecs mainWindowSpecs;
    sf::RenderWindow mainWindow(sf::VideoMode(mainWindowSpecs.getWidth(), mainWindowSpecs.getHeight()), mainWindowSpecs.getTitle());
    mainWindow.setFramerateLimit(mainWindowSpecs.getFPS());
    Reminder::TextureManager textureManager = Reminder::InitTexturesMain();                      // �������� �������

    //DemoCard(mainWindow, textureManager, mainWindowSpecs);
    ShowUI(mainWindow, textureManager, mainWindowSpecs);
}

// ���������������� ��������
void DemoCard(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs)
{
    sf::Sprite sprite(textureManager.getTexture("card1"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);     // ����� �������� � ����� �������
    sprite.setPosition(mainWindowSpecs.getWidth() / 2, mainWindowSpecs.getHeight() / 2);         // ���������������� ������� � ������ ����

    float scaleX = 0.5f; // �������� ������� �� X � Y
    const float scaleY = 0.5f;
    sprite.setScale(scaleX, scaleY);

    // ��������� ��� �������� ������ � ���������� (�������)
    bool squeezing = 1; // ����������� ��������� ��������
    bool changed = 0;   // ������ ��������
    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
        }
        if (squeezing)
        {
            scaleX -= 0.01;
        }
        else
        {
            scaleX += 0.01;
        }

        if (scaleX <= 0 or scaleX >= 0.5)         // ��������� ����������� �������� � �������� ��� ���������� ������   
        {
            if (scaleX <= 0 and changed == 0)
            {
                sprite.setTexture(textureManager.getTexture("card2"));
                changed = 1;
            }

            else if (scaleX <= 0 and changed == 1)
            {
                sprite.setTexture(textureManager.getTexture("card1"));
                changed = 0;
            }

            squeezing = !squeezing;
        }

        sprite.setScale(scaleX, scaleY);

        mainWindow.clear();
        mainWindow.draw(sprite);
        mainWindow.display();
    }

}

void ShowUI(sf::RenderWindow& mainWindow, Reminder::TextureManager& textureManager, Reminder::WindowSpecs& mainWindowSpecs)
{

    sf::Sprite background(textureManager.getTexture("Background_Main"));

    float k = mainWindow.getSize().x / textureManager.getTexture("Background_Main").getSize().x;

    background.setScale(static_cast<float>(mainWindow.getSize().x) / textureManager.getTexture("Background_Main").getSize().x,
        static_cast<float>(mainWindow.getSize().y) / textureManager.getTexture("Background_Main").getSize().y);


    sf::Sprite button1(textureManager.getTexture("Login_button"));
    sf::Sprite button2(textureManager.getTexture("Reg_button"));

    float buttonWidth = button1.getLocalBounds().width;
    float buttonHeight = button1.getLocalBounds().height;

    /* �������������� �������� � ����������� � ����������� ���� */
    float scaleX = mainWindow.getSize().x / 1920.0f;; // ������� �� ��� X
    float scaleY = mainWindow.getSize().y / 1080.0f;; // ������� �� ��� Y
    button1.setScale(scaleX, scaleY);
    button2.setScale(scaleX, scaleY);

    // �������������� ������������� ������� ������ �� �������� ���� c ����������� ���������
    float ButttonPosX = mainWindow.getSize().x / 2 - button1.getGlobalBounds().width / 2;
    float ButttonPosY = mainWindow.getSize().y / 2 - button1.getGlobalBounds().height / 2;

    button1.setPosition(ButttonPosX, ButttonPosY + mainWindow.getSize().y / 6.0);
    button2.setPosition(ButttonPosX, ButttonPosY + mainWindow.getSize().y / 30.0);

    float alpha = 255; // ��������� ������������ �������
    bool changedButton1 = 0;
    bool procAnim1 = 0;

    bool changedButton2 = 0;
    bool cancAnim2 = 0;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);
    sf::FloatRect buttonBounds = button1.getGlobalBounds();

    while (mainWindow.isOpen())
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);

        if (button1.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        {

            if (alpha > 0 and !changedButton1)
            {
                alpha -= 5.0f; // ��������� ������������ ������� �� ��������
                button1.setColor(sf::Color(alpha, alpha, alpha, 255)); // ��������� ����� ������������ �������
                procAnim1 = 1;
                changedButton1 = 0;
            }
            else if (alpha == 0)
            {
                button1.setTexture(textureManager.getTexture("Login_button_hovered"));
                alpha = 255;
                button1.setColor(sf::Color(alpha, alpha, alpha, 255));
                changedButton1 = 1;
                procAnim1 = 0;
            }
            if (procAnim1 and !changedButton1)
            {
                std::cout << "check" << "\n";
            }   
        }
        else
        {
            if (procAnim1 and !changedButton1) // ������� ������ �������� ����������
            {
                std::cout << "procAnim1 and !changedButton1" << "\n";
                alpha += 5.0f;
                button1.setColor(sf::Color(alpha, alpha, alpha, 255)); // ��������� ����� ������������ �������
                if (alpha == 255) { procAnim1 = 0; }
            }

            if (alpha > 0 and changedButton1) // ��������� �������
            {
                std::cout << "alpha > 0 and changedButton1" << "\n";
                alpha -= 5.0f; // ��������� ������������ ������� �� ��������
                button1.setColor(sf::Color(alpha, alpha, alpha, 255)); // ��������� ����� ������������ �������
                procAnim1 = 1;
                if (alpha == 0) { procAnim1 = 0; }
            }

            else if (alpha < 255 and !procAnim1) // ���������� ������� ������
            {
                std::cout << "alpha = 0" << "\n";
                alpha += 5.0f;
                std::cout << alpha << "\n";
                button1.setTexture(textureManager.getTexture("Login_button"));
                button1.setColor(sf::Color(alpha, alpha, alpha, 255));
                changedButton1 = 0;
            }
        }


        if (button2.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        {
            button2.setTexture(textureManager.getTexture("Reg_button_hovered"));
        }
        else
        {
            button2.setTexture(textureManager.getTexture("Reg_button"));
        }




        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
                
        }

        mainWindow.clear();
        mainWindow.draw(background);
        mainWindow.draw(button1);
        mainWindow.draw(button2);
        mainWindow.display();
    }
}