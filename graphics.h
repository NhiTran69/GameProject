#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "defs.h"

struct Sprite;
struct Mouse;

struct Graphics {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *bg;
    SDL_Texture *play;

    void init();
    void loadBackground(const char *name);

    void prepareScene();
    void presentScene();

    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

    void quit();
    void render(int x, int y, const Sprite& sprite);
    void renderMouse(const Mouse &mouse, const Sprite &mouseSprite);

    ~Graphics() {
        quit();
    }
};

#endif // GRAPHICS_H_INCLUDED
