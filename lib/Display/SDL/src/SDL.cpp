#include "SDL.hpp"
#include "Exception.hpp"
#include <memory>

extern "C" Arcade::SDL *Arcade::entry_point()
{
    return new Arcade::SDL;
}

Arcade::SDL::SDL()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        throw Arcade::exception("Error SDL_Init : " + std::string(SDL_GetError()));

    m_window = SDL_CreateWindow("Arcade - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                1000, 700, SDL_WINDOW_SHOWN);
    if (m_window == NULL)
        throw Arcade::exception("Error SDL_CreateWindow : " + std::string(SDL_GetError()));

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == NULL)
        throw Arcade::exception("Error SDL_CreateRenderer : " + std::string(SDL_GetError()));
}

Arcade::SDL::~SDL()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Arcade::Input Arcade::SDL::event()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                return ESCAPE;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        return LEFT;
                    case SDLK_RIGHT:
                        return RIGHT;
                    case SDLK_UP:
                        return UP;
                    case SDLK_DOWN:
                        return DOWN;
                    case SDLK_RETURN:
                        return ENTER;
                    case SDLK_SPACE:
                        return SPACE;
                    case SDLK_ESCAPE:
                        return ESCAPE;
                    case SDLK_r:
                        return RESET;
                    case SDLK_m:
                        return MENU;
                    case SDLK_n:
                        return N;
                    case SDLK_p:
                        return P;
                    case SDLK_i:
                        return I;
                    case SDLK_o:
                        return O;
                }
        }
    }
    return NIL;
}

void Arcade::SDL::refresh()
{
    SDL_RenderPresent(m_renderer);
}

void Arcade::SDL::clear()
{
    SDL_RenderClear(m_renderer);
}

void Arcade::SDL::draw(std::shared_ptr<Arcade::IObject> object)
{
    if (dynamic_cast<Arcade::Tile*>(object.get()) != nullptr) {
        auto tile = dynamic_cast<Arcade::Tile *>(object.get());
        std::shared_ptr<SDLTextureObj> tmpTexture = std::make_shared<SDLTextureObj>(tile->getPath(), m_renderer);
        tmpTexture->setPosition(tile->getPosition().first, tile->getPosition().second);
        SDL_RenderCopy(m_renderer, tmpTexture->m_img, NULL, tmpTexture->m_rect);
    }
}

Arcade::SDLTextureObj::SDLTextureObj(const std::string &path, SDL_Renderer *renderer)
    : m_img(NULL), m_rect(new SDL_Rect)
{
    m_img = IMG_LoadTexture(renderer, path.c_str());

    int w, h;
    SDL_QueryTexture(m_img, NULL, NULL, &w, &h);
    m_rect->h = h;
    m_rect->w = w;
}

void Arcade::SDLTextureObj::setPosition(unsigned int x, unsigned int y)
{
    m_rect->x = x * Arcade::tileSize;
    m_rect->y = y * Arcade::tileSize;
}

Arcade::SDLTextureObj::~SDLTextureObj()
{
    SDL_DestroyTexture(m_img);
    delete m_rect;
}
