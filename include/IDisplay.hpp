#pragma once

#include <string>
#include <vector>
#include "Input.hpp"
#include "Tile.hpp"

namespace Arcade
{
    class IDisplay
    {
	public:
        virtual ~IDisplay() = default;
		virtual Arcade::Input event() = 0;
		virtual void clear() = 0;
		virtual void refresh() = 0;
        virtual void draw(Arcade::Tile tile) = 0;
        virtual void playSound(Arcade::Sound sound) = 0;
	};
}