#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <SDL.h>
#include "sprite.h"
#include "defs.h"
#include "map.h"
#include "defs.h"
#include <vector>
using namespace std;

struct Graphics;

struct Mouse {
    int x = 0, y = 10;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    int direction = DIR_NONE;
    int width = 38;
    int height = 53;
    vector<SDL_Rect> box;
    Sprite sprite;

    Mouse(Graphics &game) {
        sprite.init(game, FIGURE_FRAMES, FIGURE_CLIPS);
        updateMouseBox();
    }

    // Hộp bap quanh nhân vật
    void updateMouseBox() {
        box.resize(10);
        box[0] = {x, y, 8, 8};
        box[1] = {x + 16, y, 6, 8};
        box[2] = {x + 30, y, 8, 8};

        box[3] = {x, y + 16, 8, 8};
        box[4] = {x + 30, y + 16, 8, 8};
        box[5] = {x, y + 29, 8, 8};
        box[6] = {x + 30, y + 29, 8, 8};

        box[7] = {x, y + 45, 8, 8};
        box[8] = {x + 16, y + 45, 6, 8};
        box[9] = {x + 30, y + 45, 8, 8};
    }

    const vector<SDL_Rect> &getMouseBox() {
        updateMouseBox();
        return box;
    }

    void reset() {
        x = 0;
        y = 10;
    }

    void move(const Map *maps) {
        SDL_Rect currentRect = {x, y, width, height};

        SDL_Rect newRect = maps->getPos(currentRect, dx, dy, getMouseBox());

        x = newRect.x;
        y = newRect.y;

        if (x < 0) x = 0;
        if (x >= SCREEN_WIDTH - width) x = SCREEN_WIDTH - width;
        if (y < 0) y = 0;
        if (y >= SCREEN_HEIGHT - height) y = SCREEN_HEIGHT - height;
    }
    void turnFront() {
        dy = speed;
        dx = 0;
        direction = DIR_FRONT;
        sprite.direction = direction;
    }
    void turnBack() {
        dy = -speed;
        dx = 0;
        direction = DIR_BACK;
        sprite.direction = direction;
    }
    void turnLeft() {
        dy = 0;
        dx = -speed;
        direction = DIR_LEFT;
        sprite.direction = direction;
    }
    void turnRight() {
        dy = 0;
        dx = speed;
        direction = DIR_RIGHT;
        sprite.direction = direction;
    }

    void stop() {
        if (direction != DIR_NONE) {
            sprite.lastDir = direction;
        }
        dx = 0;
        dy = 0;
        direction = DIR_NONE;
        sprite.direction = DIR_NONE;
    }
    void inputDir(const Uint8 *key, Map *maps) {
        stop();
        if (key[SDL_SCANCODE_UP]) {
            turnBack();
        }
        if (key[SDL_SCANCODE_DOWN]) {
            turnFront();
        }
        if (key[SDL_SCANCODE_LEFT]) {
            turnLeft();
        }
        if (key[SDL_SCANCODE_RIGHT]) {
            turnRight();
        }
        move(maps);
        sprite.tick();
    }
};
#endif // MOUSE_H_INCLUDED
