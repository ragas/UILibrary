#include "Canvas.hpp"
#include <SDL2/SDL_opengl.h>
#include <cstdlib>
#include <SDL2_ttf/SDL_ttf.h>
#include "utility.hpp"

void Canvas::drawRect(int x0, int y0, int width, int height){
  SDL_Rect rect;
  rect.x = x0-1;
  rect.y = y0-1;
  rect.w = width+2;
  rect.h = height+2;
  if(false){
    SDL_SetRenderDrawColor(window, 255,0,0,255);
    SDL_RenderDrawRect(window, &rect);
  }
}

void Canvas::drawText(std::string text, int x0,int y0,int width,int height,Color color, MapPainter* painter){
  SDL_Rect clip,dest,src;
  clip.x = x0;
  clip.y = y0;
  clip.w = width;
  clip.h = height;
  SDL_RenderSetViewport(window, &clip);

  dest.x = dest.y = 0;
  for(auto c : text){
    if(c == '\n'){
      dest.y += 0;
      dest.x = 0;
      continue;
    }
    auto sp = painter->getSprite(c);
    src.x = sp.x;
    src.y = sp.y;
    src.h = sp.height;
    src.w = sp.width;
    dest.w = sp.width;
    dest.h = sp.height;
    SDL_SetTextureColorMod(sp.texture, color.r, color.g, color.b);
    SDL_RenderCopy(window, sp.texture, &src, &dest);
    dest.x += dest.w;
    
  }
  SDL_RenderSetViewport(window, NULL);
}

void Canvas::drawSprite(Sprite sp, int x0,int y0, int width, int height){
  SDL_Rect src,dest;
  dest.x = x0;
  dest.y = y0;
  dest.w = width;
  dest.h = height;

  src.x = sp.x;
  src.y = sp.y;
  src.w = sp.width;
  src.h = sp.height;
  SDL_RenderCopy(window, sp.texture, &src, &dest);
}

void Canvas::drawSprite(Sprite sp, SDL_Texture* texture, int x0,int y0, int width, int height){
  SDL_SetRenderTarget(window, texture);
  drawSprite(sp, x0,y0,width,height);
  SDL_SetRenderTarget(window, NULL);
}

void Canvas::drawTexture(SDL_Texture* texture, int x0,int y0, int xx, int yy, int width, int height){
  SDL_Rect src,dest;
  dest.x =  x0;
  dest.y =  y0;
  dest.w = width;
  dest.h = height;  

  src.x = 0;
  src.y = 0;
  src.w = width;
  src.h = height;
  SDL_RenderCopy(window, texture, &src, &dest);
}

void Canvas::translate(int x, int y){
  trans = glm::translate(trans, glm::vec3(x,y,0));
}

void Canvas::getCurrentWorldXY(int& x, int& y){
  x = trans[3][0];
  y = trans[3][1];
}

void Canvas::clip(){
  SDL_RenderSetClipRect(window, &clipRect);
}

void Canvas::clip(int x0, int y0, int x1, int y1){
  int width = std::abs(x1-x0);
  int height = std::abs(y1-y0);
  glm::vec4 pos = trans *  glm::vec4(0,0,0,1);
  SDL_Rect rect;
  rect.x = pos.x;
  rect.y = pos.y;
  rect.w = width;
  rect.h = height;

  if(SDL_IntersectRect(&clipRect, &rect, &clipRect) == SDL_FALSE){
    clipRect.x = clipRect.y = clipRect.w = clipRect.h = 0;
  }
}

void Canvas::disableClip(){
  SDL_RenderSetClipRect(window, NULL);
}

void Canvas::save(){
  transformationStack.push({trans, clipRect});
}

void Canvas::restore(){
  if(transformationStack.size() > 0){
    auto it = transformationStack.top();
    transformationStack.pop();
    trans = it.transform;
    clipRect = it.clipRect;
  }else{
    trans = glm::mat4(1.f);
    clipRect.x=clipRect.y=0;
    clipRect.w = width; clipRect.h=height;
  }
}

