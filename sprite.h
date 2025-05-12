#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

using namespace std;

struct Graphics;

struct Sprite {
    SDL_Texture *frontTex = nullptr;
    SDL_Texture *backTex = nullptr;
    SDL_Texture *leftTex = nullptr;
    SDL_Texture *rightTex = nullptr;

    vector<SDL_Rect> clips;
    int currentFrame = 0;
    int direction = DIR_NONE;
    int lastDir = DIR_RIGHT;

    Uint32 lastFrame = 0;

    Sprite() = default;

    // Hàm init nhận renderer và load texture bên trong
    void init(Graphics &game, int frames, const int clip_[][4]);
    void tick();
    SDL_Texture* getCurrentTex() const;
    const SDL_Rect* getCurrentClip() const;
    ~Sprite();
};

inline static void capFPS(Uint32 frameStart) {
    int frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}
#endif // SPRITE_H_INCLUDED
