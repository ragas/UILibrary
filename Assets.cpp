#include "Assets.hpp"
#include <SDL2_ttf/SDL_ttf.h>

Sprite Assets::getAsset(AssetType type){
  Sprite sp;
  sp.texture = textureMap;
  sp.height = sp.width = mainMapDimen;
  if(type == AssetType::FOREST_TREE)
    sp.x = sp.y = 0;
  if(type == AssetType::FOREST_BUSH){
    sp.x = mainMapDimen;sp.y = 0;
  }
  return sp;
}

Sprite Assets::getAsset(MapAsset type){
  return mainMap[(short)type];
}

void Assets::loadAssets(SDL_Renderer* renderer){
  SDL_Surface* surf = SDL_LoadBMP("../assets/map.bmp");
  textureMap = SDL_CreateTextureFromSurface(renderer, surf);
  if(textureMap == NULL)
    debug_print(SDL_GetError());
  SDL_FreeSurface(surf);
}

void Assets::processMainMapAssets(short dimen){
  mainMapDimen = dimen;
  mainMap.resize((short)MapAsset::LAST);
  for(size_t i =0; i < mainMap.size(); ++i){
    mainMap[i].texture = textureMap;
    mainMap[i].height = mainMap[i].width = dimen;
    mainMap[i].x = i*dimen;
    mainMap[i].y = 0;
  }
}

void Assets::loadFonts(SDL_Renderer* renderer){
  debug_print("Loading Fonts");
  TTF_Font *font = TTF_OpenFont("../assets/Roboto-Medium.ttf", 16);
  if (font == nullptr){
    debug_print(TTF_GetError());
    exit(1);
    return ;
  }

  fontinfo.height = TTF_FontHeight(font);
  fontinfo.ascent = TTF_FontAscent(font);
  fontinfo.descent = TTF_FontDescent(font);
  fontinfo.lineSkip = TTF_FontLineSkip(font);

  fontTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);

  int success = SDL_SetRenderTarget(renderer, fontTexture);
  if(success != 0)
    debug_print(SDL_GetError());
  debug_print("Generating Glyphs");
  int minx,maxx,miny,maxy,advance;
  SDL_Color color={255,255,255,255};
  SDL_Rect  dest;
  dest.x = dest.y = dest.h = dest.w = 0;
  for(char c = 0x20 ; c <= 0x7E; ++c){
    TTF_GlyphMetrics(font,c,&minx,&maxx,&miny,&maxy,&advance);
    Glyph glyph;
    glyph.minx = minx;
    glyph.maxx = maxx;
    glyph.miny = miny;
    glyph.maxy = maxy;
    glyph.advance = advance;

    auto surf = TTF_RenderGlyph_Blended(font,c,color);
    auto glyphtexture = SDL_CreateTextureFromSurface(renderer, surf);

    dest.w = surf->w;
    dest.h = surf->h;
    SDL_RenderCopy(renderer, glyphtexture, NULL, &dest);
    glyph.image.texture = fontTexture;
    glyph.image.x = dest.x;
    glyph.image.y = dest.y;
    glyph.image.width = surf->w;
    glyph.image.height = surf->h;
    glyphs.push_back(glyph);
    dest.x += surf->w;
    dest.y = surf->h;
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(glyphtexture);
  }
  TTF_CloseFont(font);
  SDL_SetRenderTarget(renderer,NULL);
  debug_print("Done Generating Glyphs");
}

void Assets::getTextSize(std::string text, int& x, int& y){
  x = 0; y = 0;
  for(size_t i =0; i < text.size(); ++i){
    char c = text[i];
    c -= 0x20;
    auto&& t = glyphs[c];
    x += t.image.width;
  }
  y = fontinfo.height;
}

Sprite Assets::getFont(char c){
  return glyphs[c-0x20].image;
}

Assets::~Assets(){
  SDL_DestroyTexture(fontTexture);
  SDL_DestroyTexture(textureMap);
}
