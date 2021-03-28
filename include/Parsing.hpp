#pragma once

#include <string>
#include <vector>

namespace Arcade
{
    class Parsing
    {
    protected:
        std::vector<std::string> m_GameLibs;
        int m_GameLibsIterator;
        std::vector<std::string> m_GraphLibs;
        int m_GraphLibsIterator;
        std::string m_name;

    public:
        Parsing(int ac, char **av);
        ~Parsing() = default;
    };
}