#pragma once

#include "IDisplay.hpp"
#include <map>
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
        SDL_Rect m_rect;
        SDL_Point m_center;
        SDLTextureObj(const std::string &path, SDL_Renderer *renderer);
        SDLTextureObj(Arcade::Text text, TTF_Font *font, SDL_Renderer *renderer);
        ~SDLTextureObj();
        void setPosition(float x, float y);
    };

    class SDL : public IDisplay
    {
    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        TTF_Font *m_font;
        std::map<std::string, std::shared_ptr<SDLTextureObj>> m_texture_map;
    public:
        SDL();
        ~SDL();
        Arcade::Input event();
        void clear();
        void refresh();
        void draw(std::shared_ptr<Arcade::IObject> object);
        void drawTile(Arcade::Tile *tile);
        void playSound(Arcade::Sound *sound);
    };
    extern "C" SDL *entry_point();
}