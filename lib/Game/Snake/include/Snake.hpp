#pragma once

#include <memory>
#include <random>
#include "IGame.hpp"

using namespace std::chrono_literals;

namespace Arcade {

class Snake : public IGame {

private:

    int m_score{};
    unsigned int m_x{};
    unsigned int m_y{};
    int m_dirX;
    int m_dirY;
    unsigned int m_rotation;

    std::random_device m_rd{};
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_distrib{};

    Input m_ev{Input::NIL};

    static constexpr std::chrono::nanoseconds m_timestep{16ms};
    std::chrono::time_point<std::chrono::high_resolution_clock> m_clock{};
    int m_ticks{};

    std::vector<std::shared_ptr<Arcade::Tile>> m_buf_wall{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_buf_snake{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_buf_apple{};

    std::shared_ptr<Arcade::Sound> m_eat_sound{};

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

    /**
     * Generates a buffer containing all the assets to load
     *
     * @param ret The return value of the movements function
     * @return A buffer containing all the assets to load
     */
    std::vector<std::shared_ptr<Arcade::IObject>> generateBuffer(int ret=0);

public:

    Snake();
    ~Snake() override = default;

    int getScore() override {return m_score;};
    void reset() override;
    std::vector<std::shared_ptr<IObject>> loop(Arcade::Input ev) override;

};

extern "C" Snake *entry_point();

}