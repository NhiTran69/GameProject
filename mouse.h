#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "sprite.h"
#include "defs.h"

struct Graphics;

struct Mouse {
    int x = 100, y = 100;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    int direction = DIR_NONE;
    Sprite sprite;

    Mouse(Graphics &game) {
        sprite.init(game, FIGURE_FRAMES, FIGURE_CLIPS);
    }
    void move() {
        x += dx;
        y += dy;

        if (x < 0) x = 0;
        if (x >= SCREEN_WIDTH - 38) x = SCREEN_WIDTH - 38;
        if (y < 0) y = 0;
        if (y >= SCREEN_HEIGHT - 53) y = SCREEN_HEIGHT - 53;
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
        dx = 0;
        dy = 0;
        direction = DIR_NONE;
        sprite.direction = direction;
    }
    void inputDir(const Uint8 *key) {
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
        move();
        sprite.tick();
    }

};


#endif // MOUSE_H_INCLUDED
