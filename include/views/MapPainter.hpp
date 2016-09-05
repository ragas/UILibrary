#pragma once
#include "utility.hpp"
#include "geosim.hpp"
#include "Assets.hpp"

class MapPainter {
  Assets assets;
  SDL_Renderer* renderer;
  SDL_Texture* temp;
  Sprite getSpriteForBiomeType(BiomeType biomeType);
public:
  short mainMapTileSize;
  void setRenderer(SDL_Renderer*);
  void init();
  Sprite getSprite(Tile* t);
  Sprite getSprite(Tile* t, Pair p);
  Sprite getSprite(char c);
  SDL_Texture* getTemp(int, int);
  void loadAssets();
  void loadFonts();
  void getTextSize(std::string, int&, int&);
};

