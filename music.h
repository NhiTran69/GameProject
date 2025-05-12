#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED
using namespace std;

struct Music {
    Mix_Music *music;
    Mix_Music *loadMusic(const char *name) {
        music = Mix_LoadMUS(name);
        if (!music) {
            cerr << "Failed to load music: " << Mix_GetError() << endl;
            return nullptr;
        }
        return music;
    }
    void play() {
        if (!music) return;
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(music, -1);
        }
    }
    void pause() {
        if (Mix_PlayingMusic() == 1) Mix_PauseMusic();
    }
    void resume() {
        if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
    }
};

#endif // MUSIC_H_INCLUDED
