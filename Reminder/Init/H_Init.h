// Инициализация при запуске

#include <unordered_map>
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"

namespace Reminder
{
    class TextureManager
    {
    private:
        std::unordered_map<std::string, sf::Texture> m_textures;

    public:
        TextureManager() {}

        void loadTexture(const std::string& key, const std::string& filename)
        {
            sf::Texture texture;
            if (texture.loadFromFile(filename))
            {
                m_textures[key] = texture;
            }
            else
            {
                std::cerr << "Texture load error for key: " << key << ", from file: " << filename << std::endl;
            }
        }


        const sf::Texture& getTexture(const std::string& key)
        {
            return m_textures[key];
        }
    };

    // Функции Init
    TextureManager InitTexturesMain();
}
//TEST
