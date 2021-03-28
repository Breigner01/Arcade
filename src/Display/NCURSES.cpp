#include "../../include/NCURSES.hpp"
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

void Arcade::NCURSES::draw(Arcade::Tile tile)
{
    char tmp[2];
    tmp[0] = static_cast<char>(tile.getSymbol());
    tmp[1] = '\0';

    if (has_colors() == FALSE) {
        mvprintw(tile.getPosition().second, tile.getPosition().first, tmp);
        return;
    }

    attron(COLOR_PAIR(colormap[tile.getColor()]));
    mvprintw(tile.getPosition().second, tile.getPosition().first, tmp);
    attroff(COLOR_PAIR(tile.getColor()));
}
