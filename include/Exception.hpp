#pragma once

#include <exception>
#include <string>

namespace Arcade {

class exception : std::exception {

protected:

    const std::string m_error;

public:

    explicit exception(std::string error) : m_error(std::move(error)) {}
    [[nodiscard]] const char *what() const noexcept override {return m_error.c_str();}
};

class MissingAsset : exception {

public:

    explicit MissingAsset(std::string error) : exception(std::move(error)) {}
};

}