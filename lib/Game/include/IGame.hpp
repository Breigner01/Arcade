#pragma once

#include <vector>
#include <memory>
#include <chrono>
#include "Input.hpp"
#include "Object.hpp"

namespace Arcade {

using clock = std::chrono::high_resolution_clock;

class IGame {

public:

    virtual ~IGame() = default;

    virtual std::vector<std::shared_ptr<Arcade::IObject>> loop(Arcade::Input ev) = 0;
    virtual int getScore() = 0;
    virtual void reset() = 0;

};

}