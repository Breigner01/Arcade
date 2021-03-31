#pragma once

#include <vector>
#include <memory>
#include "Input.hpp"
#include "Object.hpp"

namespace Arcade
{
    class IGame
    {
    public:
        virtual ~IGame() = default;
        virtual std::vector<std::shared_ptr<Arcade::IObject> > loop(Arcade::Input ev) = 0;
        virtual int getScore() = 0;
        virtual void reset() = 0;
    };
}