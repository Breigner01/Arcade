#pragma once

#include "IDisplay.hpp"
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
    public:
        SFML();
        ~SFML();
        Arcade::Input event();
        void clear();
        void refresh();
        void draw(std::shared_ptr<Arcade::IObject> object);
        void playSound(Arcade::Sound *sound);
    };
    extern "C" SFML *entry_point();
}