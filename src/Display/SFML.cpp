#include "../../include/SFML.hpp"
#include "../../include/Exception.hpp"
#include <memory>

extern "C" Arcade::SFML *Arcade::entry_point()
{
    return new Arcade::SFML;
}

Arcade::SFML::SFML()
{
    m_window.create(sf::VideoMode(1000, 700), "Arcade - SFML");
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
}

Arcade::SFML::~SFML()
{
    m_window.close();
}

Arcade::Input Arcade::SFML::event()
{
    sf::Event ev;
    while (m_window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            return ESCAPE;
        if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::Up)
                return UP;
            else if (ev.key.code == sf::Keyboard::Down)
                return DOWN;
            else if (ev.key.code == sf::Keyboard::Left)
                return LEFT;
            else if (ev.key.code == sf::Keyboard::Right)
                return RIGHT;
            else if (ev.key.code == sf::Keyboard::Enter)
                return ENTER;
            else if (ev.key.code == sf::Keyboard::Space)
                return SPACE;
            else if (ev.key.code == sf::Keyboard::Escape)
                return ESCAPE;
        }
    }
    return NIL;
}

void Arcade::SFML::refresh()
{
    m_window.display();
}

void Arcade::SFML::clear()
{
    m_window.clear(sf::Color::Black);
}

void Arcade::SFML::draw(Arcade::Tile tile)
{
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
    if (!texture->loadFromFile(tile.getPath()))
        throw Arcade::exception("SFML Failed to load a texture");
    sprite->setTexture(*texture, true);
    sprite->setPosition(tile.getPosition().first * 10, tile.getPosition().second * 10);

    m_window.draw(*sprite);
}
