#pragma once

#include <exception>
#include <string>

namespace Arcade
{
    class exception : std::exception
    {
    protected:
        const std::string m_error;
    public:
        exception(const std::string &error) : m_error(error) {};
        const char *what() const noexcept override {return m_error.c_str();};
    };
}