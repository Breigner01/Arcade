#pragma once

#include "IGame.hpp"

namespace Arcade
{
    class Pacman : public IGame
    {
    private:
        int m_score;
        unsigned int m_x;
        unsigned int m_y;
    public:
        Pacman();
        ~Pacman() override = default;
        int getScore() override {return m_score;};
        void reset() override;
        std::vector<Arcade::Tile> loop(Arcade::Input ev) override;
    };
    extern "C" Pacman *entry_point();
}