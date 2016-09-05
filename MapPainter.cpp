#include "MapPainter.hpp"
Sprite MapPainter::getSprite(Tile* t){
  auto biomeType = t->getBiomeType();
  return getSpriteForBiomeType(biomeType);
}

Sprite MapPainter::getSpriteForBiomeType(BiomeType biomeType){
  if(biomeType == BiomeType::TROPICAL_FOREST_BROADLEAF_MOIST)
    return assets.getAsset(MapAsset::RAINFOREST);
  else if(biomeType == BiomeType::TEMPERATE_FOREST_BROADLEAF ||
	  biomeType == BiomeType::TROPICAL_FOREST_BROADLEAF_DRY)
    return assets.getAsset(MapAsset::DECIDUOUS_FOREST);
  else if (biomeType == BiomeType::TEMPERATE_FOREST_CONIFER ||
	   biomeType == BiomeType::TROPICAL_FOREST_CONIFER ||
	   biomeType == BiomeType::TAIGA) 
    return assets.getAsset(MapAsset::CONFIEROUS_FOREST);
  else if (biomeType == BiomeType::OCEAN)
    return assets.getAsset(MapAsset::SEA);
  else if (biomeType == BiomeType::MOUNTAIN)
    return assets.getAsset(MapAsset::MOUNTAIN);
  else if(biomeType == BiomeType::TROPICAL_GRASSLAND ||
	  biomeType == BiomeType::TEMPERATE_GRASSLAND)
    return assets.getAsset(MapAsset::GRASSLAND);
  else if(biomeType == BiomeType::DESERT)
    return assets.getAsset(MapAsset::DESERT);
  else if (biomeType == BiomeType::WETLAND)
    return assets.getAsset(MapAsset::WETLAND);
  else if (biomeType == BiomeType::TUNDRA)
    return assets.getAsset(MapAsset::TUNDRA);
  
  return assets.getAsset(MapAsset::SAVANNA);
}

Sprite MapPainter::getSprite(Tile* t, Pair p){
  auto biomeType = t->getBiomeType(p);
  return getSpriteForBiomeType(biomeType);
}

SDL_Texture* MapPainter::getTemp(int w, int h){
  return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
}

void MapPainter::loadAssets(){
  assets.loadAssets(renderer);
}

void MapPainter::loadFonts(){
  assets.loadFonts(renderer);
}

void MapPainter::getTextSize(std::string text, int& x, int& y){
  assets.getTextSize(text, x, y);
}

void MapPainter::setRenderer(SDL_Renderer* r){
  renderer = r;
}

void MapPainter::init(){
  loadFonts();
  loadAssets();
  assets.processMainMapAssets(mainMapTileSize);
}

Sprite MapPainter::getSprite(char c){
  return assets.getFont(c);
}
