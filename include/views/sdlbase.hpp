#ifndef SDLBASE_H
#define SDLBASE_H
#include <SDL2/SDL.h>
#include "gui.hpp"

namespace GUI
{
  class SDLBase{
  private:
    GUIBase* _gui;
    SDL_Window* window;
    SDL_Renderer *ren;
    bool Initialize();
    SDL_GLContext glcontext;    
    float frameTime;
    bool is_running;
    void HandleEvent(SDL_Event& event);
  public:
    SDLBase();
    void MessagePump();
    inline float getFrameTime(){return frameTime;}
    ~SDLBase();
    static SDLBase* Create(GUIBase* gui);    
  };
}
#endif
