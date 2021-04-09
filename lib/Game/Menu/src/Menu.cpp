#include <iostream>
#include <filesystem>
#include "Menu.hpp"
#include "Exception.hpp"
#include "Parsing.hpp"

extern "C" Arcade::Menu *Arcade::entry_point()
{
    return new Arcade::Menu;
}

Arcade::Menu::Menu() : m_score(0), m_iterator(0)
{
    Arcade::setTileSize(30);
    int pos = 3;

    for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
        for (auto gameLib : GAMES_LIBRARIES) {
            if (entry.path() == gameLib) {
                m_GameLibs.emplace_back(gameLib);
                std::string tmp(gameLib);
                auto other = tmp.substr(13);
                other.pop_back();
                other.pop_back();
                other.pop_back();
               // m_text_list.push_back(std::make_shared<Arcade::Text>(other, WHITE, 5, pos));
                pos += 2;
            }
        }
    }

    m_menu_title = std::make_shared<Arcade::Text>("Arcade - Menu", WHITE, 16, 1);
    m_arcade = std::make_shared<Arcade::Tile>("assets/Menu/arcade.png", 0, WHITE, 3, 3);
    m_poster = std::make_shared<Arcade::Tile>("assets/Menu/nibbler_affiche.png", 'N', WHITE, 13, 11);

    m_menu_enter = std::make_shared<Arcade::Text>("Select a game and press ENTER !", WHITE, 12, 30);
    m_menu_exit = std::make_shared<Arcade::Text>("Press ECHAP to exit Arcade", WHITE, 13, 31);
}

void Arcade::Menu::reset()
{
}

std::vector<std::shared_ptr<Arcade::IObject>> Arcade::Menu::loop(Arcade::Input ev)
{
    if (ev == RIGHT) {
        m_poster->setPath("assets/Menu/pacman_affiche.png");
       // m_poster->setSymbol('P');
        m_score--;
        if (m_score < 0)
            m_score = static_cast<int>(m_text_list.size()) - 1;
    }
    else if (ev == LEFT) {
       // m_poster->setSymbol('N');
        m_poster->setPath("assets/Menu/nibbler_affiche.png");
        m_score++;
        if (m_score >= static_cast<int>(m_text_list.size()))
            m_score = 0;
    }
    std::vector<std::shared_ptr<Arcade::IObject>> buf{};
    buf.push_back(m_arcade);
    buf.push_back(m_poster);
    buf.push_back(m_menu_title);
    buf.push_back(m_menu_enter);
    buf.push_back(m_menu_exit);
    for (const auto &txt : m_text_list)
        buf.push_back(txt);
    return buf;
}
