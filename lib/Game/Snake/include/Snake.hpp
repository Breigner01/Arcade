#pragma once

#include "IGame.hpp"

namespace Arcade
{
    class Snake : public IGame
    {
    private:
        int m_score;
        unsigned int m_x;
        unsigned int m_y;
        unsigned char direction = 8;
    public:
        Snake();
        ~Snake() override = default;
        int getScore() override {return m_score;};
        void reset() override;
        std::vector<std::shared_ptr<IObject> > loop(Arcade::Input ev) override;
    };
    extern "C" Snake *entry_point();
}