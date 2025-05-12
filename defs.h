#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define WINDOW_TITLE "Maze"
#define INITIAL_SPEED 4

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "music.h"
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 760;

const int FIGURE_CLIPS[][4] = {
    {0, 0, 38, 53},
    {38, 0, 38, 53},
    {76, 0, 38, 53},
    {114, 0, 38, 53}
};

const int FIGURE_FRAMES = 4;

const int DIR_FRONT = 0;
const int DIR_BACK = 1;
const int DIR_LEFT = 2;
const int DIR_RIGHT = 3;
const int DIR_NONE = 4;

const int FPS = 40;
const int frameDelay = 1000/FPS;
const int figureDelay = 500;

inline void logErrorAndExit(const char* msg, const char* error) {
    SDL_Log("%s: %s", msg, error);
    SDL_Quit();
    exit(1);
}

const SDL_Color textColor = {85, 114, 138, 255};
#endif // DEFS_H_INCLUDED
