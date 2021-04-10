#pragma once

#include <memory>
#include <random>
#include "IGame.hpp"
#include "HighScore.hpp"

namespace Arcade {

class Menu : public IGame {

private:

    int m_score;
    unsigned int m_iterator;
    std::shared_ptr<Arcade::Tile> m_arcade {};
    std::shared_ptr<Arcade::Tile> m_poster {};
    std::shared_ptr<Arcade::Text> m_menu_title {};
    std::shared_ptr<Arcade::Text> m_menu_enter {};
    std::shared_ptr<Arcade::Text> m_menu_exit {};
    std::vector<std::shared_ptr<Arcade::Text> > m_text_list {};
    std::vector<std::string> m_GameLibs {};
    std::shared_ptr<Arcade::Sound> m_sou {};
    HighScore m_high_scores {};

public:

    Menu();
    ~Menu() override = default;

    int getScore() override {return m_score;};
    void reset() override;
    std::vector<std::shared_ptr<IObject>> loop(Arcade::Input ev) override;
};

extern "C" Menu *entry_point();

}