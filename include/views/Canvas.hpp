#pragma once
#include "Color.hpp"
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <stack>
#include "MapPainter.hpp"

class Canvas {
  SDL_Renderer* window;
  glm::mat4 trans;
  SDL_Rect clipRect;
  int width, height;
  struct state{
    glm::mat4 transform;
    SDL_Rect clipRect;
  };
  std::stack<state> transformationStack;
public:
  inline Canvas(SDL_Renderer* rt, int width, int height):window(rt), width(width), height(height){
    window = rt;
    trans=glm::mat4(1.f);    
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = width;
    clipRect.h = height;
  }
  void drawRect(int,int,int,int);
  void drawSprite(Sprite sp, int x0,int y0, int x1, int y1);
  void drawTexture(SDL_Texture* texture, int x0,int y0, int,int,int width, int height);
  void drawSprite(Sprite sp, SDL_Texture* texture, int x0,int y0, int width, int height);
  void drawText(std::string text,int,int,int,int,Color, MapPainter*);
  void drawVerticleScrollbar(int,int,int,int);
  void translate(int,int);
  void getCurrentWorldXY(int& x, int& y);
  void clip(int x0, int y0, int x1, int y1);
  void clip();
  void disableClip();
  void save(); void restore();
};
