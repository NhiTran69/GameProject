#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

struct Sprite;
struct Mouse;

struct Graphics {
    SDL_Window *window;
    SDL_Renderer *renderer;
    void logErrorAndExit(const char* msg, const char* error);
    void init();

    void prepareScene(SDL_Texture *background = nullptr);
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
