#include "../../include/Pacman.hpp"

extern "C" Arcade::Pacman *Arcade::entry_point()
{
    return new Arcade::Pacman;
}

Arcade::Pacman::Pacman() : m_score(0), m_x(2), m_y(2)
{

}

void Arcade::Pacman::reset()
{

}

std::vector<Arcade::Tile> Arcade::Pacman::loop(Arcade::Input ev)
{
    std::vector<Arcade::Tile> buffer;

    if (ev == Input::UP)
        m_y--;
    else if (ev == Input::DOWN)
        m_y++;
    else if (ev == Input::LEFT)
        m_x--;
    else if (ev == Input::RIGHT)
        m_x++;
    for (int i = 0; i < 20; i++)
        buffer.emplace_back("assets/blue.bmp", 'V', BLUE, i, 0);
    for (int i = 0; i < 20; i++)
        buffer.emplace_back("assets/blue.bmp", 'V', BLUE, i, 4);
    for (int i = 0; i < 5; i++)
        buffer.emplace_back("assets/blue.bmp", 'V', BLUE, 0, i);
    for (int i = 0; i < 5; i++)
        buffer.emplace_back("assets/blue.bmp", 'V', BLUE, 19, i);
    buffer.emplace_back("assets/red.bmp", 'O', RED, 7, 2);
    buffer.emplace_back("assets/red.bmp", 'O', RED, 14, 2);
    buffer.emplace_back("assets/green.bmp", 'P', GREEN, m_x, m_y);
    return buffer;
}
