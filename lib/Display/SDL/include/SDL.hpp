#pragma once

#include "../../include/IDisplay.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace Arcade
{
    class SDLTextureObj
    {
    public:
        SDL_Texture *m_img;
        SDL_Rect *m_rect;
        SDLTextureObj(const std::string &path, SDL_Renderer *renderer);
        ~SDLTextureObj();
        void setPosition(unsigned int x, unsigned int y);
    };

    class SDL : public IDisplay
    {
    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
    public:
        SDL();
        ~SDL();
        Arcade::Input event();
        void clear();
        void refresh();
        void draw(std::shared_ptr<Arcade::IObject> object);
        void playSound(Arcade::Sound sound) {(void)sound;};
    };
    extern "C" SDL *entry_point();
}