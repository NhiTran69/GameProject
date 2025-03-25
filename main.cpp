#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "mouse.h"
#include "defs.h"
using namespace std;

int main(int argc, char *argv[])
{
    Graphics game;
    game.init();

    Mouse mouse(game);

    bool quit = false;
    SDL_Event e;
    const Uint8 *key = SDL_GetKeyboardState(nullptr);

    while(!quit) {
        // Xử lý sự kiện
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }

        // Cập nhật trạng thái của Mouse
        mouse.inputDir(key);

        // Xóa màn hình và chuẩn bị vẽ
        game.prepareScene();

        // Vẽ Mouse với sprite tương ứng
        game.renderMouse(mouse, mouse.sprite);

        // Hiển thị lên màn hình
        game.presentScene();

        SDL_Delay(100);
    }
    return 0;
}
