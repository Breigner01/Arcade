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
                                1920, 1080, SDL_WINDOW_SHOWN);
    if (m_window == NULL)
        throw Arcade::exception("Error SDL_CreateWindow : " + std::string(SDL_GetError()));

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == NULL)
        throw Arcade::exception("Error SDL_CreateRenderer : " + std::string(SDL_GetError()));

    if (TTF_Init() == -1)
        throw Arcade::exception("Error TTF_Init : " + std::string(TTF_GetError()));
    m_font = TTF_OpenFont("assets/font.ttf", 30);
    if (m_font == NULL)
        throw Arcade::exception("Error font not found");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        throw Arcade::exception("Error Mix_OpenAudio : " + std::string(Mix_GetError()));
}

Arcade::SDL::~SDL()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_CloseFont(m_font);
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

Arcade::Input Arcade::SDL::event()
{
    SDL_Event event;
    Arcade::Input input = NIL;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                input = ESCAPE;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        input = LEFT;
                        break;
                    case SDLK_RIGHT:
                        input = RIGHT;
                        break;
                    case SDLK_UP:
                        input = UP;
                        break;
                    case SDLK_DOWN:
                        input = DOWN;
                        break;
                    case SDLK_RETURN:
                        input = ENTER;
                        break;
                    case SDLK_SPACE:
                        input = SPACE;
                        break;
                    case SDLK_ESCAPE:
                        input = ESCAPE;
                        break;
                    case SDLK_r:
                        input = RESET;
                        break;
                    case SDLK_m:
                        input = MENU;
                        break;
                    case SDLK_n:
                        input = N;
                        break;
                    case SDLK_p:
                        input = P;
                        break;
                    case SDLK_i:
                        input = I;
                        break;
                    case SDLK_o:
                        input = O;
                        break;
                }
        }
    }
    return input;
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
    if (dynamic_cast<Arcade::DynamicTile*>(object.get()) != nullptr) {
        auto tile = dynamic_cast<Arcade::DynamicTile *>(object.get())->getActualTile();
        std::shared_ptr<SDLTextureObj> tmpTexture = std::make_shared<SDLTextureObj>(tile->getPath(), m_renderer);
        tmpTexture->setPosition(tile->getPosition().first, tile->getPosition().second);
        SDL_RenderCopyEx(m_renderer, tmpTexture->m_img, nullptr, tmpTexture->m_rect, tile->getRotation(), &tmpTexture->m_center, static_cast<SDL_RendererFlip>(SDL_FLIP_NONE));
    }
    else if (dynamic_cast<Arcade::Tile*>(object.get()) != nullptr) {
        auto tile = dynamic_cast<Arcade::Tile *>(object.get());
        std::shared_ptr<SDLTextureObj> tmpTexture = std::make_shared<SDLTextureObj>(tile->getPath(), m_renderer);
        tmpTexture->setPosition(tile->getPosition().first, tile->getPosition().second);
        SDL_RenderCopyEx(m_renderer, tmpTexture->m_img, nullptr, tmpTexture->m_rect, tile->getRotation(), &tmpTexture->m_center, static_cast<SDL_RendererFlip>(SDL_FLIP_NONE));
    }
    else if (dynamic_cast<Arcade::Text*>(object.get()) != nullptr) {
        auto text = dynamic_cast<Arcade::Text *>(object.get());
        std::shared_ptr<SDLTextureObj> tmpTexture = std::make_shared<SDLTextureObj>(*text, m_font, m_renderer);
        tmpTexture->setPosition(text->getPosition().first, text->getPosition().second);
        SDL_RenderCopy(m_renderer, tmpTexture->m_img, NULL, tmpTexture->m_rect);
    }
    else if (dynamic_cast<Arcade::Sound*>(object.get()) != nullptr)
        playSound(dynamic_cast<Arcade::Sound*>(object.get()));
}

void Arcade::SDL::playSound(Arcade::Sound *sound)
{
    auto m_music = Mix_LoadMUS(sound->getSound().c_str());
    if (!m_music)
        throw Arcade::exception("Error Mix_LoadMUS");
    Mix_PlayMusic(m_music, 1);
    Mix_FreeMusic(m_music);
}

Arcade::SDLTextureObj::SDLTextureObj(const std::string &path, SDL_Renderer *renderer)
    : m_img(NULL), m_rect(new SDL_Rect)
{
    m_img = IMG_LoadTexture(renderer, path.c_str());

    int w, h;
    SDL_QueryTexture(m_img, NULL, NULL, &w, &h);
    m_rect->h = h;
    m_rect->w = w;
    m_center.x = m_rect->w / 2;
    m_center.y = m_rect->h / 2;
}

Arcade::SDLTextureObj::SDLTextureObj(Arcade::Text text, TTF_Font *font, SDL_Renderer *renderer)
    : m_img(NULL), m_rect(new SDL_Rect)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.getText().c_str(), { 255, 255, 255, 0 });
    m_img = SDL_CreateTextureFromSurface(renderer, textSurface);
    int w, h;
    SDL_QueryTexture(m_img, NULL, NULL, &w, &h);
    m_rect->h = h;
    m_rect->w = w;
    SDL_FreeSurface(textSurface);
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
