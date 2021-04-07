#include "SFML.hpp"
#include "Exception.hpp"
#include <memory>

extern "C" Arcade::SFML *Arcade::entry_point()
{
    return new Arcade::SFML;
}

Arcade::SFML::SFML()
{
    m_window.create(sf::VideoMode(1920, 1080), "Arcade - SFML");
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(true);
    if (!m_font.loadFromFile("assets/font.ttf"))
        throw Arcade::exception("Failed to load font");
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
            else if (ev.key.code == sf::Keyboard::R)
                return RESET;
            else if (ev.key.code == sf::Keyboard::M)
                return MENU;
            else if (ev.key.code == sf::Keyboard::N)
                return N;
            else if (ev.key.code == sf::Keyboard::P)
                return P;
            else if (ev.key.code == sf::Keyboard::I)
                return I;
            else if (ev.key.code == sf::Keyboard::O)
                return O;
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

void Arcade::SFML::draw(std::shared_ptr<Arcade::IObject> object)
{
    if (dynamic_cast<Arcade::DynamicTile*>(object.get()) != nullptr) {
        auto tile = dynamic_cast<Arcade::DynamicTile *>(object.get())->getActualTile();
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
        if (!texture->loadFromFile(tile->getPath()))
            throw Arcade::exception("SFML Failed to load a texture");
        sprite->setTexture(*texture, true);
        sprite->setPosition((tile->getPosition().first * Arcade::tileSize) + Arcade::tileSize / 2, (tile->getPosition().second * Arcade::tileSize) + Arcade::tileSize / 2);
        sprite->setOrigin(Arcade::tileSize / 2, Arcade::tileSize / 2);
        sprite->setRotation(tile->getRotation());
        m_window.draw(*sprite);
    }
    else if (dynamic_cast<Arcade::Tile*>(object.get()) != nullptr) {
        auto tile = dynamic_cast<Arcade::Tile *>(object.get());
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
        if (!texture->loadFromFile(tile->getPath()))
            throw Arcade::exception("SFML Failed to load a texture");
        sprite->setTexture(*texture, true);
        sprite->setPosition((tile->getPosition().first * Arcade::tileSize) + Arcade::tileSize / 2, (tile->getPosition().second * Arcade::tileSize) + Arcade::tileSize / 2);
        sprite->setOrigin(Arcade::tileSize / 2, Arcade::tileSize / 2);
        sprite->setRotation(tile->getRotation());

        m_window.draw(*sprite);
    }
    else if (dynamic_cast<Arcade::Text*>(object.get()) != nullptr) {
        auto text = dynamic_cast<Arcade::Text *>(object.get());
        std::shared_ptr<sf::Text> txtobj = std::make_shared<sf::Text>();
        txtobj->setFont(m_font);
        txtobj->setString(text->getText());
        txtobj->setPosition(text->getPosition().first * Arcade::tileSize, text->getPosition().second * Arcade::tileSize);
        txtobj->setCharacterSize(30);

        m_window.draw(*txtobj);
    }
    else if (dynamic_cast<Arcade::Sound*>(object.get()) != nullptr)
        playSound(dynamic_cast<Arcade::Sound*>(object.get()));
}

void Arcade::SFML::playSound(Arcade::Sound *sound)
{
    auto tmpbuffer = std::make_shared<sf::SoundBuffer>();
    if (!tmpbuffer->loadFromFile(sound->getSound()))
        throw Arcade::exception("SFML Failed to load a sound");
    auto tmpsound = std::make_shared<sf::Sound>(*tmpbuffer);
    tmpsound->play();
}