#include "Snake.hpp"

extern "C" Arcade::Snake *Arcade::entry_point()
{
    return new Arcade::Snake;
}

Arcade::Snake::Snake() : m_score(0), m_x(2), m_y(2)
{

}

void Arcade::Snake::reset()
{

}

std::vector<Arcade::Tile> Arcade::Snake::loop(Arcade::Input ev)
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
        buffer.emplace_back("assets/blue.bmp", 'X', BLUE, i, 0);
    for (int i = 0; i < 20; i++)
        buffer.emplace_back("assets/blue.bmp", 'X', BLUE, i, 4);
    for (int i = 0; i < 5; i++)
        buffer.emplace_back("assets/blue.bmp", 'X', BLUE, 0, i);
    for (int i = 0; i < 5; i++)
        buffer.emplace_back("assets/blue.bmp", 'X', BLUE, 19, i);
    buffer.emplace_back("assets/green.bmp", 'H', GREEN, 7, 2);
    buffer.emplace_back("assets/green.bmp", 'H', GREEN, 14, 2);
    buffer.emplace_back("assets/red.bmp", 'O', RED, m_x, m_y);
    return buffer;
}
