#include "Snake.hpp"

extern "C" Arcade::Snake *Arcade::entry_point()
{
    return new Arcade::Snake;
}

Arcade::Snake::Snake()
    : m_score(0), m_x(2), m_y(2), dynBlock(std::make_shared<Arcade::DynamicTile>(Tile("assets/red.bmp", 'X', RED), 4))
{
    dynBlock->addTile(Tile("assets/blue.bmp", 'Y', BLUE));
    dynBlock->addTile(Tile("assets/green.bmp", 'Z', GREEN));
    dynBlock->setPosition(10, 10);
}

void Arcade::Snake::reset()
{
    m_x = 2;
    m_y = 2;
}

std::vector<std::shared_ptr<Arcade::IObject> > Arcade::Snake::loop(Arcade::Input ev)
{
    std::vector<std::shared_ptr<Arcade::IObject> > buffer;

    if (ev == Input::UP)
        direction = 1;
    else if (ev == Input::DOWN)
        direction = 2;
    else if (ev == Input::LEFT)
        direction = 4;
    else if (ev == Input::RIGHT)
        direction = 8;
    for (int i = 0; i < 20; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, i, 0));
    for (int i = 0; i < 20; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, i, 4));
    for (int i = 0; i < 5; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, 0, i));
    for (int i = 0; i < 5; i++)
        buffer.push_back(std::make_shared<Tile>("assets/blue.bmp", 'X', BLUE, 19, i));
    buffer.push_back(std::make_shared<Tile>("assets/green.bmp", 'H', GREEN, 7, 2));
    buffer.push_back(std::make_shared<Tile>("assets/green.bmp", 'H', GREEN, 14, 2));
    auto player = std::make_shared<Tile>("assets/red.bmp", 'O', RED, m_x, m_y);
    player->setRotation(90);
    buffer.push_back(player);
    buffer.push_back(std::make_shared<Text>("Press M to return to menu", RED, 3, 5));
    buffer.push_back(dynBlock);
    dynBlock->animate();
    buffer.push_back(std::make_shared<Sound>("assets/sound.wav"));
    switch (direction) {
        case 1:
            m_y--;
            break;
        case 2:
            m_y++;
            break;
        case 4:
            m_x--;
            break;
        case 8:
            m_x++;
            break;
    }
    return buffer;
}
