#pragma once

#include <string>
#include <utility>

namespace Arcade
{
    constexpr int tileSize = 50;

    enum Color {WHITE, BLACK, RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN};

    class IObject
    {
    public:
        virtual ~IObject() = default;
    };

    class Tile : public IObject
    {
    private:
        // For SFML and SDL
        std::string m_path;
        unsigned int m_rotation;
        // For NCURSES
        unsigned char m_symbol;
        Arcade::Color m_color;
        // For Both;
        std::pair<unsigned int, unsigned int> m_pos;
    public:
        Tile(std::string path_to_bmp, unsigned char symbol, Arcade::Color color = WHITE, unsigned int x = 0, unsigned int y = 0)
                : m_path(std::move(path_to_bmp)), m_rotation(0), m_symbol(symbol), m_color(color), m_pos(std::make_pair(x, y)) {};
        ~Tile() = default;
        // GETTERS
        std::string getPath() const {return m_path;};
        unsigned char getSymbol() const {return m_symbol;};
        Arcade::Color getColor() const {return m_color;};
        std::pair<unsigned int, unsigned int> getPosition() const {return m_pos;};
        unsigned int getRotation() const {return m_rotation;};
        // SETTERS
        void setPath(std::string path_to_bmp) {m_path = std::move(path_to_bmp);};
        void setSymbol(unsigned char symbol) {m_symbol = symbol;};
        void setColor(Arcade::Color color) {m_color = color;};
        void setPosition(unsigned int x, unsigned int y) {m_pos.first = x; m_pos.second = y;};
        void setRotation(unsigned int angle) {m_rotation = angle;};
    };

    class Sound : public IObject
    {
    private:
        std::string m_path;
    public:
        Sound(std::string path) : m_path(std::move(path)) {};
        ~Sound() = default;
        std::string getSound() const {return m_path;};
        void setSound(std::string path) {m_path = std::move(path);};
    };

    class Text : public IObject
    {
    private:
        std::string m_text;
        Arcade::Color m_color;
        std::pair<unsigned int, unsigned int> m_pos;
    public:
        Text(std::string text, Arcade::Color color = WHITE, unsigned int x = 0, unsigned int y = 0) : m_text(std::move(text)), m_color(color), m_pos(std::make_pair(x, y)) {};
        ~Text() = default;
        void setText(std::string text) {m_text = std::move(text);};
        void setColor(Arcade::Color color) {m_color = color;};
        void setPosition(unsigned int x, unsigned int y) {m_pos.first = x; m_pos.second = y;};
        std::string getText() const {return m_text;};
        Arcade::Color getColor() const {return m_color;};
        std::pair<unsigned int, unsigned int> getPosition() const {return m_pos;};
    };
}