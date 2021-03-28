#pragma once

#include "IGame.hpp"

namespace Arcade
{
    class Pacman : public IGame
    {
    private:
        int m_score;
    public:
        Pacman();
        ~Pacman() override = default;
        int getScore() override {return m_score;};
        bool isGameOver() override {return false;};
        void reset() override;
        std::vector<Arcade::Tile> loop(Arcade::Input ev) override;
    };
    extern "C" Pacman *entry_point();
}