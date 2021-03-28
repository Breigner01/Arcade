#pragma once

#include <iostream>
#include <vector>
#include <exception>

namespace Utils
{
    class exception : public std::exception
    {
    protected:
        const std::string m_error;
    public:
        exception(const std::string &error) : m_error(error) {};
        const char *what() const noexcept override {return m_error.c_str();};
    };
    struct CMD
    {
        std::string output;
        int returnValue;
    };
    CMD getCMD(const std::string &command);
    std::string getFile(const std::string &path);
    std::vector<std::string> stringToVector(const std::string &str, char separator, bool pushEmptyStrings = false);
};