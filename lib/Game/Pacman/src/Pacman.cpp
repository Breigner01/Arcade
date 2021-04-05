#include <fstream>
#include <sstream>
#include "Pacman.hpp"
#include "CoordinatesCompute.hpp"
#include "Exception.hpp"

extern "C" Arcade::Pacman *Arcade::entry_point()
{
    return new Arcade::Pacman;
}

Arcade::Pacman::Pacman() : m_x(2), m_y(2)
{
    std::ifstream stream("assets/Pacman/map.txt");
    std::ostringstream content;

    if (stream.fail())
        throw Arcade::MissingAsset("Missing map for Pacman");
    content << stream.rdbuf();
    m_map.assign(content.str());
    std::erase_if(m_map, [](char c) { return (c == 'Z'); });
    for (auto &c : m_map)
        if (c == '\n')
            m_nbLines += 1;
    while (m_map[m_lineLen] != '\n')
        m_lineLen += 1;
}

void Arcade::Pacman::reset()
{
    m_x = 2;
    m_y = 2;
}


int Arcade::Pacman::checkForCollisions(int dir_x, int dir_y)
{
    if (dir_x != 0 && dir_y != 0)
        return (-1);
    std::size_t pos = computeIndex(m_x + dir_x, m_y + dir_y, m_lineLen);
    if (m_map[pos] == m_wall)
        return (1);
    else if (m_map[pos] == m_phantom)
        return (2);
    return (0);
}

std::vector<std::shared_ptr<Arcade::IObject>>Arcade::Pacman::loop(Arcade::Input ev)
{
    std::vector<std::shared_ptr<Arcade::IObject>> buffer;

    if (ev == Input::UP)
        m_y--;
    else if (ev == Input::DOWN)
        m_y++;
    else if (ev == Input::LEFT)
        m_x--;
    else if (ev == Input::RIGHT)
        m_x++;
    for (int i = 0; i < 20; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'V', BLUE, i, 0));
    for (int i = 0; i < 20; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'V', BLUE, i, 4));
    for (int i = 0; i < 5; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'V', BLUE, 0, i));
    for (int i = 0; i < 5; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'V', BLUE, 19, i));
    buffer.push_back(std::make_shared<Tile>("assets/red.bmp", 'O', RED, 7, 2));
    buffer.push_back(std::make_shared<Tile>("assets/red.bmp", 'O', RED, 14, 2));
    buffer.push_back(std::make_shared<Tile>("assets/green.bmp", 'P', GREEN, m_x, m_y));
    return buffer;
}
