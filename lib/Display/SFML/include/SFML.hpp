#pragma once

#include "IDisplay.hpp"
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

namespace Arcade
{
    class SFML : public IDisplay
    {
    private:
        sf::RenderWindow m_window;
        sf::Font m_font;
        std::map<std::string, std::shared_ptr<sf::Texture>> m_texture_map;
    public:
        SFML();
        ~SFML();
        Arcade::Input event();
        void clear();
        void refresh();
        void draw(std::shared_ptr<Arcade::IObject> object);
        void drawTile(Arcade::Tile *tile);
        void playSound(Arcade::Sound *sound);
    };
    extern "C" SFML *entry_point();
}