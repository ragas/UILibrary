#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "utility.hpp"
#include <string>

struct Sprite {
  SDL_Texture* texture;
  unsigned int x,y;
  unsigned short height;
  unsigned short width;
};

enum AssetType{
  FOREST_TREE,
  FOREST_BUSH
};

enum class MapAsset : short{
  CONFIEROUS_FOREST,
    RAINFOREST,    
    DECIDUOUS_FOREST,
    SEA,
    MOUNTAIN,
    GRASSLAND,
    DESERT,
    WETLAND,
    TUNDRA,
    RIVER,
    SAVANNA,
    LAST,
    };

struct Font {
  int height, ascent, descent, lineSkip;
};

struct Glyph {
  Sprite image;
  int minx,maxx,miny,maxy,advance;
};

class Assets{
  Font fontinfo;
  std::vector<Sprite> mainMap;
  short mainMapDimen;
  std::vector<Glyph> glyphs;
  SDL_Texture* textureMap;
  SDL_Texture* fontTexture;
public:
  ~Assets();
  void loadAssets(SDL_Renderer* renderer);
  void processMainMapAssets(short dimen);
  void loadFonts(SDL_Renderer* renderer);
  void getTextSize(std::string text, int& x, int& y);
  Sprite getAsset(AssetType);
  Sprite getAsset(MapAsset);
  Sprite getFont(char c);
};
