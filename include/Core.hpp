#pragma once

#include "Parsing.hpp"
#include "IGame.hpp"
#include "IDisplay.hpp"
#include "DyLib.hpp"

namespace Arcade
{
    class Core : public Parsing
    {
    private:
        DyLib<Arcade::IGame> m_game;
        DyLib<Arcade::IDisplay> m_display;
    public:
        Core(int ac, char **av);
        ~Core() = default;
        void prevDisplay();
        void nextDisplay();
        void prevGame();
        void nextGame();
        bool menu();
    };
}