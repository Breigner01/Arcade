#pragma once

#include "IGame.hpp"
#include <memory>

namespace Arcade
{
    class Snake : public IGame
    {
    private:

        int m_score;
        unsigned int m_x;
        unsigned int m_y;
        unsigned char direction = 8;
        std::shared_ptr<Arcade::DynamicTile> dynBlock;

        std::string m_map;
        unsigned int m_nbLines{};
        unsigned int m_lineLen{};

        static constexpr char m_snakeHead = 'N';
        static constexpr char m_snake = 'S';
        static constexpr char m_wall = 'X';
        static constexpr char m_apple = 'A';

        /**
         * Checks for collisions with a wall or an enemy
         *
         * @param dir_x -1, 0 or 1 to indicates which direction to look at on the X axis
         * @param dir_y -1, 0 or 1 to indicates which direction to look at on the Y axis
         * @return -1 on error,
         *          0 if no collision will happen,
         *          1 if there is a wall,
         *          2 if it is an apple,
         *          3 if it is a part of the snake's body
         */
        int checkForCollisions(int dir_x, int dir_y);

    public:

        Snake();
        ~Snake() override = default;

        int getScore() override {return m_score;};
        void reset() override;
        std::vector<std::shared_ptr<IObject>> loop(Arcade::Input ev) override;
    };
    extern "C" Snake *entry_point();
}