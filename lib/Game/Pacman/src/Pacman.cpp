#include <fstream>
#include <sstream>
#include <iostream>
#include "Pacman.hpp"
#include "CoordinatesCompute.hpp"
#include "Exception.hpp"

extern "C" Arcade::Pacman *Arcade::entry_point()
{
    return new Arcade::Pacman;
}

Arcade::Pacman::Pacman()
{
    Arcade::setTileSize(50);
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

    int x = 0;
    int y = 0;
    for (auto &c : m_map) {
        if (c == '\n') {
            y += 1;
            x = 0;
            continue;
        } else if (c == m_pacman1) {
            m_pacman_buf.push_back(std::make_shared<Arcade::Tile>(m_pacman1Asset, m_pacman1, YELLOW, x, y));
            m_x = x;
            m_y = y;
        } else if (c == m_wall)
            m_wall_buf.push_back(std::make_shared<Arcade::Tile>("assets/Pacman/wall.png", m_wall, BLUE, x, y));
        else if (c == m_phantom) {
            m_phantoms_buf.push_back(std::make_shared<Arcade::Tile>(m_phantomsAssets[m_phantoms_buf.size()],
                                                                    m_phantom, m_phantomsColors[m_phantoms_buf.size()],
                                                                    x, y));
            m_phantomInitCoords.push_back(std::make_pair<unsigned int, unsigned int>(x, y));
        } else if (c == m_dot)
            m_dots_buf.push_back(std::make_shared<Arcade::Tile>("assets/Pacman/dot.png", m_dot, WHITE, x, y));
        else if (c == m_pacGum)
            m_pacGum_buf.push_back(std::make_shared<Arcade::Tile>("assets/Pacman/pac_gum.png", m_pacGum, WHITE, x, y));
        else if (c == m_door)
            m_doors_buf.push_back(std::make_shared<Arcade::Tile>("assets/Pacman/door.png", m_door, ORANGE, x, y));
        x += 1;
    }
}

void Arcade::Pacman::reset()
{
    m_x = 2;
    m_y = 2;
}

int Arcade::Pacman::movements(int dirX, int dirY, int rotation)
{
    int x = m_x + dirX;
    int y = m_y + dirY;

    if (x == -1)
        x = m_lineLen - 1;
    else if (x == m_lineLen)
        x = 0;
    if ((dirX != 0 && dirY != 0) || y > m_nbLines)
        return (-1);
    m_pacman_buf[0]->setRotation(rotation);
    std::size_t pos = computeIndex(x, y, m_lineLen);
    if (m_map[pos] == m_dot) {
        m_score += 1;
        int i = 0;
        for (auto &dot : m_dots_buf) {
            auto coords = dot->getPosition();
            if (coords.first == x && coords.second == y) {
                m_dots_buf.erase(m_dots_buf.cbegin() + i);
                break;
            }
            i += 1;
        }
    } else if (m_map[pos] == m_pacGum) {
        int i = 0;
        for (auto &pacGum : m_pacGum_buf) {
            auto pacGumPos = pacGum->getPosition();
            if (pacGumPos.first == x && pacGumPos.second == y) {
                m_pacGum_buf.erase(m_pacGum_buf.cbegin() + i);
                break;
            }
            i += 1;
        }
        for (auto &&elem : m_vulnerable)
            elem = true;
        m_timer = 100;
    } else if (m_map[pos] == m_phantom)
        return (1);
    else if (m_map[pos] == m_vulnerablePhantom) {
        int nb = 0;
        for (auto &&elem : m_vulnerable)
            if (!elem)
                nb += 1;
        m_score += 200 + (200 * nb);
        for (std::size_t i = 0; i < m_vulnerable.size(); i++) {
            auto phantomPos = m_phantoms_buf[i]->getPosition();
            if (phantomPos.first == x && phantomPos.second == y) {
                m_vulnerable[i] = false;
                m_phantoms_buf[i]->setPosition(m_phantomInitCoords[i].first, m_phantomInitCoords[i].second);
            }
        }
    } else if (m_map[pos] == m_wall || m_map[pos] == '_')
        return (0);
    m_map[computeIndex(m_x, m_y, m_lineLen)] = ' ';
    m_map[pos] = 'C';
    m_pacman_buf[0]->setPosition(x, y);
    m_pacman_buf[0]->setSymbol(m_pacman_buf[0]->getSymbol() == m_pacman1 ? m_pacman2 : m_pacman1);
    m_pacman_buf[0]->setPath(m_pacman_buf[0]->getPath() == "assets/Pacman/pacman1.png" ? m_pacman2Asset :
    m_pacman1Asset);
    m_x = x;
    m_y = y;
    return (0);
}

std::vector<std::shared_ptr<Arcade::IObject>> Arcade::Pacman::loop(Arcade::Input ev)
{
    int ret = 0;

    if (m_timer != 0) {
        m_timer -= 1;
        if (m_timer == 0)
            for (auto &&elem : m_vulnerable)
                elem = false;
    }

    switch (ev) {
        case Input::UP:
            ret = movements(0, -1, 270);
            break;
        case Input::DOWN:
            ret = movements(0, 1, 90);
            break;
        case Input::LEFT:
            ret = movements(-1, 0, 180);
            break;
        case Input::RIGHT:
            ret = movements(1, 0, 0);
            break;
    }
    std::cout << m_map << std::endl;
    if (ret == -1)
        std::cout << "An error occurred" << std::endl;
    else if (ret == 1)
        std::cout << "Game Over" << std::endl;
    std::vector<std::shared_ptr<Arcade::IObject>> buf{};
    for (auto &elem : m_pacman_buf)
        buf.push_back(elem);
    for (auto &elem : m_wall_buf)
        buf.push_back(elem);
    for (auto &elem : m_phantoms_buf)
        buf.push_back(elem);
    for (auto &elem : m_dots_buf)
        buf.push_back(elem);
    for (auto &elem : m_pacGum_buf)
        buf.push_back(elem);
    for (auto &elem : m_doors_buf)
        buf.push_back(elem);
    return (buf);
}
