#include "Snake.hpp"
#include "CoordinatesCompute.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

extern "C" Arcade::Snake *Arcade::entry_point()
{
    return new Arcade::Snake;
}

Arcade::Snake::Snake()
    : m_score(0), m_x(2), m_y(2), dynBlock(std::make_shared<Arcade::DynamicTile>(Tile("assets/red.bmp", 'X', RED), 4))
{
    std::ifstream stream("assets/Snake/map.txt");
    std::ostringstream content;

    content << stream.rdbuf();
    m_map.assign(content.str());
    for (auto &c : m_map)
        if (c == '\n')
            m_nbLines += 1;
    while (m_map[m_lineLen] != '\n')
        m_lineLen += 1;
    dynBlock->addTile(Tile("assets/blue.bmp", 'Y', BLUE));
    dynBlock->addTile(Tile("assets/green.bmp", 'Z', GREEN));
    dynBlock->setPosition(10, 10);

    int x = 0;
    int y = 0;
    for (auto &c : m_map) {
        if (c == '\n') {
            y += 1;
            x = 0;
            continue;
        }
        if (c == m_snake) {
            m_buf_snake.push_back(std::make_shared<Tile>("assets/blue.bmp", m_snake, BLUE, x, y));
        }
        if (c == m_wall) {
            m_buf_wall.push_back(std::make_shared<Tile>("assets/green.bmp", m_wall, GREEN, x, y));
        }
        if (c == m_apple) {
            m_buf_apple.push_back(std::make_shared<Tile>("assets/red.bmp", m_apple, RED, x, y));
        }
        if (c == m_snakeHead) {
            m_buf_snake.push_back(std::make_shared<Tile>("assets/test.png", m_snakeHead, MAGENTA, x, y));
            m_x = x;
            m_y = y;
        }
        x += 1;
    }
}

void Arcade::Snake::reset()
{
    m_x = 2;
    m_y = 2;
}

int Arcade::Snake::checkForCollisions(int dir_x, int dir_y)
{
    if (dir_x != 0 && dir_y != 0)
        return (-1);
    std::size_t pos = computeCoordinates(m_x + dir_x, m_y + dir_y, m_lineLen);
    if (m_map[pos] == m_wall)
        return (1);
    else if (m_map[pos] == m_apple)
        return (2);
    else if (m_map[pos] == m_snake)
        return (3);
    return (0);
}

std::vector<std::shared_ptr<Arcade::IObject>> Arcade::Snake::loop(Arcade::Input ev)
{
    std::vector<std::shared_ptr<Arcade::IObject>> buf;
    if (ev == Input::UP)
        direction = Input::UP;
    else if (ev == Input::DOWN)
        direction = Input::DOWN;
    else if (ev == Input::LEFT)
        direction = Input::LEFT;
    else if (ev == Input::RIGHT)
        direction = Input::RIGHT;
//    for (int i = 0; i < 20; i++)
//        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, i, 0));
//    for (int i = 0; i < 20; i++)
//        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, i, 4));
//    for (int i = 0; i < 5; i++)
//        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, 0, i));
//    for (int i = 0; i < 5; i++)
//        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, 19, i));
//    buffer.push_back(std::make_shared<Tile>("assets/green.bmp", 'H', GREEN, 7, 2));
//    buffer.push_back(std::make_shared<Tile>("assets/green.bmp", 'H', GREEN, 14, 2));
//    auto player = std::make_shared<Tile>("assets/red.bmp", 'O', RED, m_x, m_y);
//    player->setRotation(90);
//    buffer.push_back(player);
//    buffer.push_back(std::make_shared<Text>("Press M to return to menu", RED, 3, 5));
//    buffer.push_back(dynBlock);
    m_buf_snake[0]->setPosition(m_x, m_y);
    dynBlock->animate();
   // buffer.push_back(std::make_shared<Sound>("assets/theme_main.ogg"));
    switch (direction) {
        case Input::UP:
            m_y--;
            break;
        case Input::DOWN:
            m_y++;
            break;
        case Input::LEFT:
            m_x--;
            break;
        case Input::RIGHT:
            m_x++;
            break;
    }


    for (auto &elem : m_buf_apple)
        buf.push_back(elem);
    for (auto &elem : m_buf_wall)
        buf.push_back(elem);
    for (auto &elem : m_buf_snake)
        buf.push_back(elem);
    return buf;
}
