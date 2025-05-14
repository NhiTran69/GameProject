#include "graphics.h"
#include "mouse.h"
#include "defs.h"
#include "map.h"
#include "text.h"
#include "time.h"
using namespace std;

int main(int argc, char *argv[])
{
    Graphics game;
    game.init();
    SDL_Texture *play = game.loadTexture("Image\\play.png");
    SDL_Texture *next = game.loadTexture("Image\\next.png");
    SDL_Texture *icon = game.loadTexture("Image\\icon1.png");
    SDL_Texture *off = game.loadTexture("Image\\icon2.png");

    game.loadBackground("Image\\bg.png");

    vector<const char*> level = {"map1.txt", "map2.txt", "map3.txt", "map4.txt"};
    int cnt(0);

    Mouse mouse(game);
    Map *maps = nullptr; // Sử dụng con trỏ

    Text timeText(game.renderer);
    timeText.initFont("Linotte Semi Bold.ttf", 29);
    Time gameTime;
    gameTime.start();

    bool quit = false;
    bool isPlay = false; // trạng thái chơi
    bool isMenu = true; // trạng thái menu
    bool isWin = false;
    bool isMusic = true;
    SDL_Texture *youWin = game.loadTexture("Image\\win.png");
    SDL_Event e;
    const Uint8 *key = SDL_GetKeyboardState(nullptr);

    Music music;
    music.loadMusic("muaha.mp3");
    music.play();

    while(!quit) {
        Uint32 frameStart = SDL_GetTicks();
        // Xử lý sự kiện
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
            else if (isMenu && e.type == SDL_MOUSEBUTTONDOWN
                     && e.button.button == SDL_BUTTON_LEFT) {
                int x = e.button.x;
                int y = e.button.y;
                if (x >= 365 && x <= 635 && y >= 320 && y <= 440) {
                    isMenu = false;
                    isPlay = true;
                    cnt = 0;
                    delete maps; // Giải phóng bộ nhớ cũ
                    maps = new Map(game, level[cnt]); // Tạo mới
                    mouse.reset();
                    gameTime.stop();
                    gameTime.start();
                    isWin = false;
                }
            }
            else if (isPlay && isWin && e.type == SDL_MOUSEBUTTONDOWN
                     && e.button.button == SDL_BUTTON_LEFT) {
                int x = e.button.x;
                int y = e.button.y;
                if (x >= 400 && x <= 600 && y >= 400 && y <= 470 && cnt + 1 < (int)level.size()) {
                    cnt++;
                    delete maps; // Giải phóng bộ nhớ cũ
                    maps = new Map(game, level[cnt]); // Tạo mới
                    mouse.reset();
                    gameTime.stop();
                    gameTime.start();
                    isWin = false;
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN
                && e.button.button == SDL_BUTTON_LEFT) {
                int x = e.button.x;
                int y = e.button.y;
                if (x >= 900 && x <= 960 && y >= 40 && y <= 100) {
                    if (isMusic) {
                        //game.loadTexture(off, 900, 40);
                        music.pause();
                        isMusic = false;
                    }
                    else {
                        music.resume();
                        isMusic = true;
                    }
                }
            }
        }

        if (isPlay &&!isWin) {
            mouse.inputDir(key, maps);
            isWin = maps->checkWin(mouse);
            if (isWin) {
                gameTime.stop();
            }
        }

        // Xóa màn hình và chuẩn bị vẽ
        game.prepareScene();
        game.renderTexture(icon, 900, 40);

        if (isMenu) {
            game.renderTexture(play, 365, 320);
        }
        else if (isPlay) {
            maps->drawMap(game);

            // Vẽ Mouse với sprite tương ứng
            game.renderMouse(mouse, mouse.sprite);

            gameTime.showTime(timeText, 830, 170);

            if (isWin) {
                game.renderTexture(youWin, 355, 290);
                if (cnt + 1 < (int)level.size()) {
                    game.renderTexture(next, 400, 400);
                }
            }
        }

        if (!isMusic) game.renderTexture(off, 900, 44);
        game.presentScene(); // Hiển thị lên màn hình
        capFPS(frameStart);  // Giới hạn FPS
    }
    delete maps;
    if (youWin != nullptr) {
        SDL_DestroyTexture(youWin);
    }
    if (play != nullptr) {
        SDL_DestroyTexture(play);
    }
    if (next != nullptr) {
        SDL_DestroyTexture(next);
    }
    game.quit();
    SDL_Quit();
    return 0;
}
