#include "Core.hpp"
#include <unistd.h>
#include <iostream>

Arcade::Core::Core(int ac, char **av) : Arcade::Parsing(ac, av)
{
    m_display.loadLib(m_GraphLibs[m_GraphLibsIterator]);
    m_game.loadLib(m_GameLibs[m_GameLibsIterator]);

    while (true) {
        auto input = m_display.get()->event();
        if (input == ESCAPE)
            break;
        else if (input == P)
            prevDisplay();
        else if (input == N)
            nextDisplay();
        else if (input == I)
            prevGame();
        else if (input == O)
            nextGame();
        else if (input == RESET)
            m_game.get()->reset();
        else {
            auto buffer = m_game.get()->loop(input);
            m_display.get()->clear();
            for (auto &tile : buffer)
                m_display.get()->draw(tile);
            m_display.get()->refresh();
        }
        usleep(2000 * 60); // 60 == framerate
    }
}

void Arcade::Core::prevDisplay()
{
    m_GraphLibsIterator--;
    if (m_GraphLibsIterator < 0)
        m_GraphLibsIterator = static_cast<int>(m_GraphLibs.size()) - 1;
    m_display.loadLib(m_GraphLibs[m_GraphLibsIterator]);
}

void Arcade::Core::nextDisplay()
{
    m_GraphLibsIterator++;
    if (m_GraphLibsIterator >= static_cast<int>(m_GraphLibs.size()))
        m_GraphLibsIterator = 0;
    m_display.loadLib(m_GraphLibs[m_GraphLibsIterator]);
}

void Arcade::Core::prevGame()
{
    m_GameLibsIterator--;
    if (m_GameLibsIterator < 0)
        m_GameLibsIterator = static_cast<int>(m_GameLibs.size()) - 1;
    m_game.loadLib(m_GameLibs[m_GameLibsIterator]);
}

void Arcade::Core::nextGame()
{
    m_GameLibsIterator++;
    if (m_GameLibsIterator >= static_cast<int>(m_GameLibs.size()))
        m_GameLibsIterator = 0;
    m_game.loadLib(m_GameLibs[m_GameLibsIterator]);
}
