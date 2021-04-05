#include <fstream>
#include <iostream>
#include <sstream>
#include "Snake.hpp"
#include "CoordinatesCompute.hpp"
#include "Exception.hpp"

extern "C" Arcade::Snake *Arcade::entry_point()
{
    return new Arcade::Snake;
}

Arcade::Snake::Snake() : m_x(2), m_y(2), m_dirX(1), m_dirY(0), m_rotate(270), m_gen(m_rd())
{
    std::ifstream stream("assets/Snake/map.txt");
    std::ostringstream content;

    if (stream.fail())
        throw Arcade::MissingAsset("Missing map for Nibbler");
    content << stream.rdbuf();
    m_map.assign(content.str());
    for (auto &c : m_map)
        if (c == '\n')
            m_nbLines += 1;
    while (m_map[m_lineLen] != '\n')
        m_lineLen += 1;

    m_distrib.param(std::uniform_int_distribution<>::param_type(0, m_map.size()));

    int x = 0;
    int y = 0;
    for (auto &c : m_map) {
        if (c == '\n') {
            y += 1;
            x = 0;
            continue;
        } else if (c == m_snake) {
            m_buf_snake.push_back(std::make_shared<Tile>("assets/Snake/snake.png", m_snake, BLUE, x, y));
        } else if (c == m_wall) {
            m_buf_wall.push_back(std::make_shared<Tile>("assets/Snake/wall.png", m_wall, GREEN, x, y));
        } else if (c == m_snakeHead) {
            m_buf_snake.push_back(std::make_shared<Tile>("assets/Snake/snake_head.png", m_snakeHead, MAGENTA, x, y));
            m_x = x;
            m_y = y;
        }
        x += 1;
    }
    generateNewApple();
}

void Arcade::Snake::reset()
{
    m_x = 2;
    m_y = 2;
}

int Arcade::Snake::movements()
{
    unsigned int x = m_x + m_dirX;
    unsigned int y = m_y + m_dirY;

    if ((m_dirX != 0 && m_dirY != 0) || x >= m_lineLen || y >= m_nbLines)
        return (-1);
    std::size_t pos = computeIndex(x, y, m_lineLen);
    m_buf_snake[0]->setRotation(m_rotate);
    if (m_map[pos] == m_wall || m_map[pos] == m_snake)
        return (1);
    else if (m_map[pos] == m_apple) {
        m_score += 1;
        int i = 0;
        for (auto &apple : m_buf_apple) {
            auto applePos = apple->getPosition();
            if (applePos.first == x && applePos.second == y) {
                m_buf_apple.erase(m_buf_apple.cbegin() + i);
                break;
            }
            i += 1;
        }
        m_buf_snake.emplace_back(m_buf_snake[m_buf_snake.size() - 1]);
        for (std::size_t j = m_buf_snake.size() - 2; j > 1; j--) {
            auto prevPos = m_buf_snake[j - 1]->getPosition();
            m_buf_snake[j]->setPosition(prevPos.first, prevPos.second);
            m_map[computeIndex(prevPos.first, prevPos.second, m_lineLen)] = 'S';
        }
        generateNewApple();
    } else {
        auto tailPos = m_buf_snake[m_buf_snake.size() - 1]->getPosition();
        m_map[computeIndex(tailPos.first, tailPos.second, m_lineLen)] = ' ';
        for (std::size_t j = m_buf_snake.size() - 1; j > 1; j--) {
            auto prevPos = m_buf_snake[j - 1]->getPosition();
            m_buf_snake[j]->setPosition(prevPos.first, prevPos.second);
            m_map[computeIndex(prevPos.first, prevPos.second, m_lineLen)] = 'S';
        }
    }
    m_buf_snake[0]->setPosition(x, y);
    m_map[computeIndex(x, y, m_lineLen)] = 'N';
    m_x = x;
    m_y = y;
    return (0);
}

void Arcade::Snake::generateNewApple()
{
    int index;

    do {
        index = m_distrib(m_gen);
    } while (m_map[index] != ' ');
    m_map[index] = m_apple;

    auto pos = computeCoordinates(index, m_lineLen);
    m_buf_apple.emplace_back(std::make_shared<Arcade::Tile>("assets/red.bmp", m_apple, RED, pos.first, pos.second));
}

std::vector<std::shared_ptr<Arcade::IObject>> Arcade::Snake::loop(Arcade::Input ev)
{
    switch (ev) {
        case Input::UP:
            m_dirX = 0;
            m_dirY = -1;
            m_rotate = 180;
            break;
        case Input::DOWN:
            m_dirX = 0;
            m_dirY = 1;
            m_rotate = 0;
            break;
        case Input::LEFT:
            m_dirX = -1;
            m_dirY = 0;
            m_rotate = 90;
            break;
        case Input::RIGHT:
            m_dirX = 1;
            m_dirY = 0;
            m_rotate = 270;
            break;
    }
    int ret = movements();
    if (ret == -1)
        std::cout << "An error occurred" << std::endl;
    else if (ret == 1)
        std::cout << "Game Over" << std::endl;

    std::vector<std::shared_ptr<Arcade::IObject>> buf{};
    buf.reserve(m_buf_snake.size() + m_buf_apple.size() + m_buf_wall.size());
    for (auto &elem : m_buf_wall)
        buf.push_back(elem);
    for (auto &elem : m_buf_snake)
        buf.push_back(elem);
    for (auto &elem : m_buf_apple)
        buf.push_back(elem);
    return buf;
}
