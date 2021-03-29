#pragma once

#include "IDisplay.hpp"
#include <iostream>

namespace Arcade
{
    class NCURSES : public IDisplay
    {
    public:
        NCURSES();
        ~NCURSES();
        Arcade::Input event();
        void clear();
        void refresh();
        void draw(Arcade::Tile tile);
        void playSound(Arcade::Sound sound) {(void)(sound);};
    };
    extern "C" NCURSES *entry_point();
}