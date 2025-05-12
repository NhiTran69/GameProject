#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SDL.h>
#include <vector>
using namespace std;

struct Graphics;
struct Mouse;

struct Tile {
    int id;
    SDL_Texture *texture;
    int width;
    int height;
};

struct Tileset {
    vector<Tile> tiles;

    Tileset() = default;
    void addTile(Graphics &game, int id, const char *name);
    ~Tileset();
    SDL_Texture *getTileTex(int id) const;
    SDL_Rect getTileRect(int id) const;
};

struct MapTile {
    int id;
    SDL_Rect rect;
};

struct Map {
    Tileset tileset;
    vector<MapTile> tiles;
    SDL_Rect winTile;

    Map(Graphics &game, const char *name);
    ~Map();
    void drawMap(Graphics &game);
    int getTileId(int x, int y) const;
    bool isWalk(int x, int y) const;
    bool canMove(vector<SDL_Rect> &box) const;
    bool checkWin(const Mouse& mouse) const;
    SDL_Rect getPos(const SDL_Rect &currentPos, int dx, int dy, const vector<SDL_Rect> &box) const;
};
#endif // MAP_H_INCLUDED
