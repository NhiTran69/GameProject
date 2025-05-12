#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "graphics.h"
#include "defs.h"

struct Text {
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Texture *mText;
    int mWidth;
    int mHeight;

    // Constructor để khởi tạo renderer và font
    Text(SDL_Renderer *renderer) : renderer(renderer), font(nullptr), mText(nullptr), mWidth(0), mHeight(0) {}

    // Destructor để giải phóng font
    ~Text() {
        if (font) {
            TTF_CloseFont(font);
        }
        if (mText) SDL_DestroyTexture(mText);
    }

    void initFont(const char *fontPath, int fontSize) {
        font = TTF_OpenFont(fontPath, fontSize);
        if (!font) {
            logErrorAndExit("Font could not be loaded! SDL_ttf Error: ", TTF_GetError());
        }
    }

    void freeTexture() {
        if (mText) {
            SDL_DestroyTexture(mText);
            mText = nullptr;
            mWidth = 0;
            mHeight = 0;
        }
    }

    void renderText(const char* text, int x, int y, SDL_Color textColor) {
        freeTexture(); // Giải phóng texture cũ
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
        if (!textSurface) {
            logErrorAndExit("Failed to create text surface", TTF_GetError());
            return;
        }

        // Tạo texture từ surface
        mText = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!mText) {
            logErrorAndExit("Failed to create text texture", SDL_GetError());
            SDL_FreeSurface(textSurface);
            return;
        }

        mWidth = textSurface->w;
        mHeight = textSurface->h;
        SDL_FreeSurface(textSurface);

        // Vẽ texture lên màn hình
        SDL_Rect render = {x, y, mWidth, mHeight};
        SDL_RenderCopy(renderer, mText, nullptr, &render);
    }

};
#endif // TEXT_H_INCLUDED
