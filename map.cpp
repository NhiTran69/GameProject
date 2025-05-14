#include "map.h"
#include "graphics.h"
#include "mouse.h"
#include "defs.h"

using namespace std;

void Tileset::addTile(Graphics &game, int id, const char *name) {
    SDL_Texture *texture = game.loadTexture(name);
    if (!texture) {
        logErrorAndExit("Failed to load tile texture", IMG_GetError());
    }

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    Tile tile;
    tile.id = id;
    tile.texture = texture;
    tile.width = w;
    tile.height = h;
    tiles.push_back(tile);
}

Tileset::~Tileset() {
    for (auto &tile : tiles) {
        if (tile.texture) SDL_DestroyTexture(tile.texture);
    }
}

SDL_Texture* Tileset::getTileTex(int id) const {
    for (const auto &tile : tiles) {
        if (tile.id == id) return tile.texture;
    }
    return nullptr;
}

SDL_Rect Tileset::getTileRect(int id) const {
    for (const auto &tile : tiles) {
        if (tile.id == id) return {0, 0, tile.width, tile.height};
    }
    return {0, 0, 0, 0};
}
Map::Map(Graphics &game, const char* name) {
    tileset.addTile(game, 0, "Image\\0.png");
    tileset.addTile(game, 1, "Image\\1.png");
    tileset.addTile(game, 2, "Image\\2.png");
    tileset.addTile(game, 3, "Image\\3.png");
    tileset.addTile(game, 4, "Image\\4.png");
    tileset.addTile(game, 7, "Image\\7.png");
    tileset.addTile(game, 9, "Image\\9.png");

    ifstream file(name);
    string line;
    int y(0);
    if(file) {
        while (getline(file, line)) {
            istringstream val(line);
            int tileId = 0;
            int height = 0, x = 0;

            vector<int> row;
            while (val >> tileId) {
                SDL_Rect tileRect = tileset.getTileRect(tileId);
                row.push_back(tileId);
                height = tileRect.h;
            }
            for (int id : row) {
                SDL_Rect tileRect = tileset.getTileRect(id);
                SDL_Rect posRect = {x, y, tileRect.w, tileRect.h};
                tiles.push_back({id, posRect});
                if (id == 9) {
                    winTile = posRect;
                }
                x += tileRect.w;
            }
            y += height;
        }
    }
    file.close();
}
Map::~Map() {
    tiles.clear();
}

void Map::drawMap(Graphics &game) {
    for (const auto &tile : tiles) {
        SDL_Texture *texture = tileset.getTileTex(tile.id);
        SDL_Rect src = tileset.getTileRect(tile.id);
        if (texture) {
            game.blitRect(texture, &src, tile.rect.x, tile.rect.y);
        }
    }
}

int Map::getTileId(int x, int y) const {
    for (const auto &tile: tiles) {
        if (x >= tile.rect.x && x < tile.rect.x + tile.rect.w &&
            y >= tile.rect.y && y < tile.rect.y + tile.rect.h) {
            return tile.id;
        }
    }
    return 1;
}

bool Map::isWalk(int x, int y) const {
    int tileId = getTileId(x, y);
    return (tileId == 0 || tileId == 2 || tileId == 3 || tileId == 9);
}

bool Map::canMove(vector<SDL_Rect> &box) const {
    for (int i = 0; i <box.size(); i++) {
        int left = box[i].x;
        int right = box[i].x + box[i].w - 1;
        int top = box[i].y;
        int bottom = box[i].y + box[i].h - 1;

        if (!isWalk(left, top) ||
            !isWalk(right, top) ||
            !isWalk(left, bottom) ||
            !isWalk(right, bottom)) {
            return false;
        }
    }
    return true;
}

bool Map::checkWin(const Mouse& mouse) const {
    int mouseX = mouse.x;
    int mouseY = mouse.y;
    return (mouseX >= winTile.x && mouseX < winTile.x + winTile.w &&
            mouseY >= winTile.y && mouseY < winTile.y + winTile.h);
}

SDL_Rect Map::getPos(const SDL_Rect &currentPos, int dx, int dy, const vector<SDL_Rect> &box) const {
    if (dx == 0 && dy == 0) return currentPos;
    vector<SDL_Rect> nextBox = box;
    SDL_Rect nextPos = currentPos;

    int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    // Di chuyển trục x
    for (int i = 0; i < abs(dx); i++) {
        nextPos.x += stepX;
        for (auto &rect: nextBox) {
            rect.x += stepX;
        }
        if (!canMove(nextBox)) {
            nextPos.x -= stepX;
            for (auto &rect : nextBox) {
                rect.x -= stepX;
            }
            break;
        }
    }

    // Di chuyển trục Y
    for (int i = 0; i < abs(dy); i++) {
        nextPos.y += stepY;
        for (auto &rect: nextBox) {
            rect.y += stepY;
        }
        if (!canMove(nextBox)) {
            nextPos.y -= stepY;
            for (auto &rect : nextBox) {
                rect.y -= stepY;
            }
            break;
        }
    }
    return nextPos; // Trả về vị trí cuối cùng sau khi di chuyển
}
