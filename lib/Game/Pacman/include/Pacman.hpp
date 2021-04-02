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
        std::string m_map;
        int m_nbLines{};
        int m_lineLen{};

        static constexpr char m_pacman1 = 'C';
        static constexpr char m_pacman2 = 'c';
        static constexpr char m_wall = 'X';
        static constexpr char m_phantom = 'P';

        /**
         * Checks for collisions with a wall or an enemy
         *
         * @param dir_x -1, 0 or 1 to indicates which direction to look at on the X axis
         * @param dir_y -1, 0 or 1 to indicates which direction to look at on the Y axis
         * @return -1 on error,
         *          0 if no collision will happen,
         *          1 if there is a wall,
         *          2 if it is an enemy
         */
        int checkForCollisions(int dir_x, int dir_y);

    public:

        Pacman();
        ~Pacman() override = default;

        int getScore() override {return m_score;};
        void reset() override;
        std::vector<std::shared_ptr<IObject>>loop(Arcade::Input ev) override;
    };
    extern "C" Pacman *entry_point();
}