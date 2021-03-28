#pragma once

#include <string>
#include <vector>
#include "IDisplay.hpp"

namespace Arcade
{
    class IGame
    {
    public:
        virtual ~IGame() = default;
        virtual std::vector<Arcade::Tile> loop(Arcade::Input ev) = 0;
        virtual int getScore() = 0;
        virtual bool isGameOver() = 0;
        virtual void reset() = 0;
    };
}