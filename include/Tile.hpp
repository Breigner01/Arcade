#pragma once

#include <string>
#include <utility>

namespace Arcade
{
    enum Color {WHITE, BLACK, RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN};

    class Tile
    {
    private:
        // For SFML and SDL
        std::string m_path;
        // For NCURSES
        unsigned char m_symbol;
        Arcade::Color m_color;
        // For Both;
        std::pair<unsigned int, unsigned int> m_pos;
    public:
        Tile(std::string path_to_bmp, unsigned char symbol, Arcade::Color color = WHITE, unsigned int x = 0, unsigned int y = 0)
                : m_path(std::move(path_to_bmp)), m_symbol(symbol), m_color(color) {m_pos = std::make_pair(x, y);};
        ~Tile() = default;
        // GETTERS
        std::string getPath() const {return m_path;};
        unsigned char getSymbol() const {return m_symbol;};
        Arcade::Color getColor() const {return m_color;};
        std::pair<unsigned int, unsigned int> getPosition() const {return m_pos;};
        // SETTERS
        void setPath(std::string path_to_bmp) {m_path = std::move(path_to_bmp);};
        void setSymbol(unsigned char symbol) {m_symbol = symbol;};
        void setColor(Arcade::Color color) {m_color = color;};
        void setPosition(unsigned int x, unsigned int y) {m_pos.first = x; m_pos.second = y;};
    };

    class Sound
    {
    private:
        std::string m_path;
    public:
        Sound(std::string path) : m_path(std::move(path)) {};
        ~Sound() = default;
        std::string getSound() const {return m_path;};
        void setSound(std::string path) {m_path = std::move(path);};
    };
}