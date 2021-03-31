#pragma once

#include <memory>
#include "Input.hpp"
#include "Object.hpp"

namespace Arcade
{
    class IDisplay
    {
	public:
        virtual ~IDisplay() = default;
		virtual Arcade::Input event() = 0;
		virtual void clear() = 0;
		virtual void refresh() = 0;
        virtual void draw(std::shared_ptr<Arcade::IObject> object) = 0;
        virtual void playSound(Arcade::Sound sound) = 0;
	};
}