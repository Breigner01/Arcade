#pragma once

#include "../../include/IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace Arcade
{
    class SFML : public IDisplay
    {
    private:
        sf::RenderWindow m_window;
    public:
        SFML();
        ~SFML();
        Arcade::Input event();
        void clear();
        void refresh();
        void draw(std::shared_ptr<Arcade::IObject> object);
        void playSound(Arcade::Sound sound) {(void)sound;};
    };
    extern "C" SFML *entry_point();
}