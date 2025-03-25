#include "graphics.h"
#include "sprite.h"
#include "mouse.h"
#include "defs.h"

// Định nghĩa các hàm của Sprite
void Sprite::init(Graphics &game, int frames, const int clip_[][4]) {
    // Load texture cho từng hướng bằng Graphics::loadTexture
    frontTex = game.loadTexture("Image\\Blue_Front.png");
    backTex = game.loadTexture("Image\\Blue_Back.png");
    leftTex = game.loadTexture("Image\\Blue_Left.png");
    rightTex = game.loadTexture("Image\\Blue_Right.png");


    SDL_Rect clip;
    for (int i = 0; i < frames; i++) {
        clip.x = clip_[i][0];
        clip.y = clip_[i][1];
        clip.w = clip_[i][2];
        clip.h = clip_[i][3];
        clips.push_back(clip);
    }
}

void Sprite::tick() {
    if (direction != DIR_NONE) {
        currentFrame = (currentFrame + 1) % clips.size();
        lastDir = direction;
    }
}

SDL_Texture* Sprite::getCurrentTex() const {
    switch (direction) {
        case DIR_FRONT: return frontTex;
        case DIR_BACK: return backTex;
        case DIR_LEFT: return leftTex;
        case DIR_RIGHT: return rightTex;
        case DIR_NONE:
            switch (lastDir) {
                case DIR_FRONT: return frontTex;
                case DIR_BACK: return backTex;
                case DIR_LEFT: return leftTex;
                case DIR_RIGHT: return rightTex;
                default: return rightTex;
            }
        default: return rightTex;
    }
}

const SDL_Rect* Sprite::getCurrentClip() const {
    if (direction == DIR_NONE) {
        return &clips[FIGURE_FRAMES - 1];
    }
    return &(clips[currentFrame]);
}

Sprite::~Sprite() {
    if (frontTex) SDL_DestroyTexture(frontTex);
    if (backTex) SDL_DestroyTexture(backTex);
    if (leftTex) SDL_DestroyTexture(leftTex);
    if (rightTex) SDL_DestroyTexture(rightTex);
}


// Định nghĩa các hàm của Graphics

void Graphics::logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                   "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("SDL_Init", SDL_GetError());
    }

    // Tạo cửa sổ
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logErrorAndExit("CreateWindow", SDL_GetError());
    }

    // Khởi tạo SDL_image
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        logErrorAndExit( "SDL_image error:", IMG_GetError());
    }

    // Tạo renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        logErrorAndExit("CreateRenderer", SDL_GetError());
    }
    // Cài đặt chất lượng phép biến đổi hình ảnh
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene(SDL_Texture *background){
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
}

void Graphics::presentScene(){
    SDL_RenderPresent(renderer);
}

SDL_Texture *Graphics::loadTexture(const char *filename){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Loading %s", filename);
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,
                       "Load texture %s", IMG_GetError());
    }
    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y){
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y){
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(renderer, texture, src, &dest);
}

void Graphics::quit(){
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::render(int x, int y, const Sprite& sprite) {
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect renderQuad = {x, y, clip->w, clip->h};
    SDL_RenderCopy(renderer, sprite.getCurrentTex(), clip, &renderQuad);
}

void Graphics::renderMouse(const Mouse &mouse, const Sprite &mouseSprite) {
    render(mouse.x, mouse.y, mouse.sprite);
}
