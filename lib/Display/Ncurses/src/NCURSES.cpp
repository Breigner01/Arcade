#include "NCURSES.hpp"
#include <ncurses.h>
#include <map>

extern "C" Arcade::NCURSES *Arcade::entry_point()
{
    return new Arcade::NCURSES;
}

std::map<Arcade::Color, unsigned int> colormap {
        {Arcade::Color::BLACK, 0},
        {Arcade::Color::RED, 1},
        {Arcade::Color::GREEN, 2},
        {Arcade::Color::YELLOW, 3},
        {Arcade::Color::BLUE, 4},
        {Arcade::Color::MAGENTA, 5},
        {Arcade::Color::CYAN, 6},
        {Arcade::Color::WHITE, 7},
        {Arcade::Color::ORANGE, 8},
        {Arcade::Color::PINK, 9},
};

Arcade::NCURSES::NCURSES()
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    timeout(100);
    curs_set(FALSE);

    start_color();
    init_pair(0, COLOR_BLACK, 0);
    init_pair(1, COLOR_RED, 0);
    init_pair(2, COLOR_GREEN, 0);
    init_pair(3, COLOR_YELLOW, 0);
    init_pair(4, COLOR_BLUE, 0);
    init_pair(5, COLOR_MAGENTA, 0);
    init_pair(6, COLOR_CYAN, 0);
    init_pair(7, COLOR_WHITE, 0);
    init_pair(8, 14, 0);
    init_pair(9, 40, 0);
}

Arcade::NCURSES::~NCURSES()
{
    endwin();
}

Arcade::Input Arcade::NCURSES::event()
{
    auto c = getch();
    if (c == KEY_UP)
        return UP;
    else if (c == KEY_DOWN)
        return DOWN;
    else if (c == KEY_LEFT)
        return LEFT;
    else if (c == KEY_RIGHT)
        return RIGHT;
    else if (c == 10)
        return ENTER;
    else if (c == 32)
        return SPACE;
    else if (c == 27)
        return ESCAPE;
    else if (c == 114)
        return RESET;
    else if (c == 109)
        return MENU;
    else if (c == 110)
        return N;
    else if (c == 112)
        return P;
    else if (c == 105)
        return I;
    else if (c == 111)
        return O;
    return NIL;
}

void Arcade::NCURSES::refresh()
{
    wrefresh(stdscr);
}

void Arcade::NCURSES::clear()
{
    wclear(stdscr);
}

void Arcade::NCURSES::draw(std::shared_ptr<Arcade::IObject> object)
{
    if (dynamic_cast<Arcade::DynamicTile*>(object.get()) != nullptr) {
        auto tile = dynamic_cast<Arcade::DynamicTile*>(object.get())->getActualTile();
        char tmp[2];
        tmp[0] = static_cast<char>(tile->getSymbol());
        tmp[1] = '\0';

        if (has_colors() == FALSE) {
            mvprintw(tile->getPosition().second, tile->getPosition().first, tmp);
            return;
        }
        attron(COLOR_PAIR(colormap[tile->getColor()]));
        mvprintw(tile->getPosition().second, tile->getPosition().first, tmp);
        attroff(COLOR_PAIR(tile->getColor()));
    }
    else if (dynamic_cast<Arcade::Tile*>(object.get()) != nullptr) {
        auto tile = dynamic_cast<Arcade::Tile*>(object.get());
        char tmp[2];
        tmp[0] = static_cast<char>(tile->getSymbol());
        tmp[1] = '\0';

        if (has_colors() == FALSE) {
            mvprintw(tile->getPosition().second, tile->getPosition().first, tmp);
            return;
        }
        attron(COLOR_PAIR(colormap[tile->getColor()]));
        mvprintw(tile->getPosition().second, tile->getPosition().first, tmp);
        attroff(COLOR_PAIR(tile->getColor()));
    }
    else if (dynamic_cast<Arcade::Text*>(object.get()) != nullptr) {
        auto text = dynamic_cast<Arcade::Text*>(object.get());

        if (has_colors() == FALSE) {
            mvprintw(text->getPosition().second, text->getPosition().first, text->getText().c_str());
            return;
        }
        attron(COLOR_PAIR(colormap[text->getColor()]));
        mvprintw(text->getPosition().second, text->getPosition().first, text->getText().c_str());
        attroff(COLOR_PAIR(text->getColor()));
    }
}
