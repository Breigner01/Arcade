#include "../../include/Pacman.hpp"

extern "C" Arcade::Pacman *Arcade::entry_point()
{
    return new Arcade::Pacman;
}

Arcade::Pacman::Pacman() : m_score(0)
{

}

void Arcade::Pacman::reset()
{

}

std::vector<Arcade::Tile> Arcade::Pacman::loop(Arcade::Input ev)
{
    std::vector<Arcade::Tile> m;
    return m;
}
