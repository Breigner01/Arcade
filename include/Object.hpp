#pragma once

#include <string>
#include <utility>
#include <vector>

namespace Arcade
{
    static int tileSize = 50;

    enum Color {WHITE, BLACK, RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN, ORANGE, PINK};

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
        ~Tile() override = default;
        // GETTERS
        [[nodiscard]] std::string getPath() const {return m_path;};
        [[nodiscard]] unsigned char getSymbol() const {return m_symbol;};
        [[nodiscard]] Arcade::Color getColor() const {return m_color;};
        [[nodiscard]] std::pair<unsigned int, unsigned int> getPosition() const {return m_pos;};
        [[nodiscard]] unsigned int getRotation() const {return m_rotation;};
        // SETTERS
        void setPath(std::string path_to_bmp) {m_path = std::move(path_to_bmp);};
        void setSymbol(unsigned char symbol) {m_symbol = symbol;};
        void setColor(Arcade::Color color) {m_color = color;};
        void setPosition(unsigned int x, unsigned int y) {m_pos.first = x; m_pos.second = y;};
        void setRotation(unsigned int angle) {m_rotation = angle;};
    };

    class DynamicTile : public IObject
    {
    private:
        std::vector<Arcade::Tile> m_tiles;
        size_t m_iterator;
        size_t m_recurence_max;
        size_t m_recurence_actual;
    public:
        explicit DynamicTile(const Tile &main_tile, unsigned int recurence = 0)
        : m_iterator(0), m_recurence_max(recurence), m_recurence_actual(0)
        {m_tiles.push_back(main_tile);};
        ~DynamicTile() override = default;
        // GETTERS
        [[nodiscard]] std::pair<unsigned int, unsigned int> getPosition() const {return m_tiles[m_iterator].getPosition();};
        [[nodiscard]] unsigned int getRotation() const {return m_tiles[m_iterator].getRotation();};
        Arcade::Tile *getActualTile() {return &m_tiles[m_iterator];};
        // SETTERStile
        void setPosition(unsigned int x, unsigned int y)
        {
            for (auto &tile : m_tiles)
                tile.setPosition(x, y);
        };
        void setRotation(unsigned int angle)
        {
            for (auto &tile : m_tiles)
                tile.setRotation(angle);
        };
        void addTile(const Arcade::Tile &tile)
        {
            m_tiles.push_back(tile);
        };
        void animate()
        {
            if (m_recurence_actual != m_recurence_max) {
                m_recurence_actual++;
                return;
            }
            m_iterator++;
            m_recurence_actual = 0;
            if (m_iterator == m_tiles.size())
                m_iterator = 0;
        };
    };

    class Sound : public IObject
    {
    private:
        std::string m_path;
    public:
        explicit Sound(std::string path) : m_path(std::move(path)) {};
        ~Sound() override = default;
        [[nodiscard]] std::string getSound() const {return m_path;};
        void setSound(std::string path) {m_path = std::move(path);};
    };

    class Text : public IObject
    {
    private:
        std::string m_text;
        Arcade::Color m_color;
        std::pair<unsigned int, unsigned int> m_pos;
    public:
        explicit Text(std::string text, Arcade::Color color = WHITE, unsigned int x = 0, unsigned int y = 0) : m_text(std::move(text)), m_color(color), m_pos(std::make_pair(x, y)) {};
        ~Text() override = default;
        void setText(std::string text) {m_text = std::move(text);};
        void setColor(Arcade::Color color) {m_color = color;};
        void setPosition(unsigned int x, unsigned int y) {m_pos.first = x; m_pos.second = y;};
        [[nodiscard]] std::string getText() const {return m_text;};
        [[nodiscard]] Arcade::Color getColor() const {return m_color;};
        [[nodiscard]] std::pair<unsigned int, unsigned int> getPosition() const {return m_pos;};
    };
}