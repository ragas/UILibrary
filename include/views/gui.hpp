#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "InputEvents.hpp"
#include <queue>
#include "utility.hpp"

namespace GUI{
  class GUIBase{
  private:
    std::string title;
    int width, height;
  protected:
    GUIBase();
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::queue<InputEventPtr> inputEventQ;
    float frameTime;
  public:
    virtual ~GUIBase(void);
    virtual void Initialize();
    virtual void TimedUpdate(float dtime)=0;
    virtual void SetFrameTime(float dtime);
    virtual void UntimedUpdate() = 0;
    virtual void Render(float dtime)=0;
    void AddInputEvent(InputEventPtr&);
    void SetTitle(std::string& _name)    {title = _name;}
    std::string GetTitle() const { return title;}
    
    void SetResolution(int x, int y) {width = x; height = y;}
    int GetWidth() const {return width;}
    int GetHeight() const {return height;}
    
    double GetCurrentTime();
    void MainLoop();
    
    inline void SetWindow(SDL_Window* window){
      GUIBase::getInstance()->window = window;
    }
    inline void SetRenderer(SDL_Renderer* r){
      GUIBase::getInstance()->renderer = r;
    }
    static GUIBase* getInstance();
  };
}
