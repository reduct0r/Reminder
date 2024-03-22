#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Horizontal Squeeze Simulation");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("Textures/card.jpg")) 
    {
        return -1;
    }

    sf::Texture texture2;
    if (!texture2.loadFromFile("Textures/card2.jpg")) 
    {
        return -1;
    }

    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);     // Точка поворота в центр спрайта
    sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);                          // Позиционирование спрайта в центре окна
    
    float scaleX = 0.5f; // Исходный масштаб по X и Y
    const float scaleY = 0.5f; 
    sprite.setScale(scaleX, scaleY);


    // Параметры для анимации сжатия и расширения (поворот)
    bool squeezing = 1; // Направление изменения масштаба
    bool changed = 0;   // Замена текстуры
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (squeezing) 
        {
            scaleX -= 0.01;
        }
        else 
        {
            scaleX += 0.01;
        }
  
        if (scaleX <= 0 or scaleX >= 0.5)         // Изменение направления анимации и текстуры при достижении границ   
        {
            if (scaleX <= 0 and changed == 0)
            {
                sprite.setTexture(texture2);
                changed = 1;
            }

            else if (scaleX <= 0 and changed == 1)
            {
                sprite.setTexture(texture);
                changed = 0;
            }

            squeezing = !squeezing;
        }

        sprite.setScale(scaleX, scaleY);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}