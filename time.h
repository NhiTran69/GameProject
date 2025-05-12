#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#include "defs.h"
using namespace std;

struct Time {
    bool mStarted = false;
    Uint32 mStartedTicks = 0;

    void start() {
        mStarted = true;
        mStartedTicks = getTicks();
    }
    void stop() {
        mStarted = false;
        mStartedTicks = 0;
    }

    Uint32 getTicks() {
        Uint32 timer = 0;
        if (mStarted) {
            timer = SDL_GetTicks() - mStartedTicks;
        }
        return timer;
    }

    bool isStarted() {
        return mStarted;
    }

    void showTime(Text &timeText, int x, int y) {
        Uint32 ticks = getTicks() / 1000; // Thời gian tính bằng giây
        Uint32 minutes = ticks / 60;
        Uint32 seconds = ticks % 60;

        char timeStr[16];
        snprintf(timeStr, sizeof(timeStr), "Time: %02d:%02d", minutes, seconds);
        timeText.renderText(timeStr, x, y, textColor);
    }
};
#endif // TIME_H_INCLUDED
