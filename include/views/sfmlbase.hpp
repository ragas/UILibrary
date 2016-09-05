#pragma once
#include "gui.hpp"

namespace GUI
{
  class GlewBase
  {
  private:
    GUIBase* _gui;
    bool is_running;
    float frameTime;
    sf::RenderWindow* window;
    bool Initialize();
    void HandleEvent();
  public:
    void MessagePump();
    static GlewBase* Create(GUIBase* gui);
    float getFrameTime() const{return frameTime;};
  };
}
