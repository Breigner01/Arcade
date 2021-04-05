#pragma once

#include <memory>
#include <random>
#include "IGame.hpp"

namespace Arcade {

class Snake : public IGame {

private:

    int m_score{};
    unsigned int m_x;
    unsigned int m_y;
    int m_dirX;
    int m_dirY;
    unsigned int m_rotate;

    std::random_device m_rd{};
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_distrib{};

    std::vector<std::shared_ptr<Arcade::Tile>> m_buf_wall{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_buf_snake{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_buf_apple{};

    std::string m_map{};
    unsigned int m_nbLines{};
    unsigned int m_lineLen{};

    static constexpr char m_snakeHead = 'N';
    static constexpr char m_snake = 'S';
    static constexpr char m_wall = 'X';
    static constexpr char m_apple = 'A';

    /**
     * Checks for collisions with a wall or an enemy
     *
     * @return -1 on error,
     *          0 if no collision will happen,
     *          1 if there is a wall or a part of the snake's body
     */
    int movements();

    /**
     * Generates a new apple at a random position on the map
     */
    void generateNewApple();

public:

    Snake();
    ~Snake() override = default;

    int getScore() override {return m_score;};
    void reset() override;
    std::vector<std::shared_ptr<IObject>> loop(Arcade::Input ev) override;
};

extern "C" Snake *entry_point();

}