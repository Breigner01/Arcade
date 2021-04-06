#pragma once

#include <memory>
#include <string_view>
#include "IGame.hpp"

namespace Arcade {

class Pacman : public IGame {

private:

    int m_score{};
    unsigned int m_x{};
    unsigned int m_y{};
    unsigned int m_timer{};

    std::vector<std::shared_ptr<Arcade::Tile>> m_pacman_buf{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_wall_buf{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_phantoms_buf{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_dots_buf{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_pacGum_buf{};
    std::vector<std::shared_ptr<Arcade::Tile>> m_doors_buf{};

    std::vector<bool> m_vulnerable{};
    std::vector<std::pair<unsigned int, unsigned int>> m_phantomInitCoords;

    std::string m_map{};
    unsigned int m_nbLines{};
    unsigned int m_lineLen{};

    const char *m_phantomsAssets[4] = {"assets/Pacman/blue_enemy.png",
                                       "assets/Pacman/orange_enemy.png",
                                       "assets/Pacman/pink_enemy.png",
                                       "assets/Pacman/red_enemy.png"};
    static constexpr Color m_phantomsColors[] = {CYAN, ORANGE, PINK, RED};

    const char *m_pacman1Asset = "assets/Pacman/pacman1.png";
    const char *m_pacman2Asset = "assets/Pacman/pacman2.png";

    static constexpr char m_pacman1 = 'C';
    static constexpr char m_pacman2 = 'c';
    static constexpr char m_wall = 'X';
    static constexpr char m_phantom = 'A';
    static constexpr char m_vulnerablePhantom = 'V';
    static constexpr char m_dot = '.';
    static constexpr char m_pacGum = 'o';
    static constexpr char m_door = '_';

    /**
     * Checks for collisions with a wall or an enemy
     *
     * @param dirX The direction on the X axis
     * @param dirY The direction on the Y axis
     * @param rotation The angle to rotate the Pacman Sprite
     * @return -1 on error,
     *          0 if no collision will happen,
     *          1 if there is an enemy
     */
    int movements(int dirX, int dirY, int rotation);

public:

    Pacman();
    ~Pacman() override = default;

    int getScore() override {return m_score;};
    void reset() override;
    std::vector<std::shared_ptr<IObject>> loop(Arcade::Input ev) override;

};

extern "C" Pacman *entry_point();

}