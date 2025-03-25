#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define WINDOW_TITLE "Maze"
#define INITIAL_SPEED 6
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

#endif // DEFS_H_INCLUDED
