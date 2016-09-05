#include "InputEvents.hpp"
#include <string>
const int MousePressed::type = 0;
const int MouseReleased::type = 1;
const int MouseMoved::type = 2;
const int WindowsResized::type = 3;
const int TextEvent::type = 4;
const int KeyEvent::type = 5;

WindowsResized::WindowsResized(int w, int h):width(w), height(h){
}

MouseMoved::MouseMoved(Button b, int xx, int yy):MouseEvent(b,xx,yy){
}

MouseReleased::MouseReleased(Button b, int xx, int yy):MouseEvent(b,xx,yy){
}

MousePressed::MousePressed(Button b, int xx, int yy):MouseEvent(b,xx,yy){
}

TextEvent::TextEvent(std::string c):code(c){}

KeyEvent::KeyEvent(Kind k, bool a, bool s, bool c, bool sys, KeyCode cd):
  kind(k), alt(a), shift(s), ctrl(c), system(sys), code(cd)
{}

InputEventPtr WindowsResized::make(int xx, int yy){
  auto p = std::unique_ptr<WindowsResized>(new WindowsResized(xx,yy));
  return std::move(p);
}

InputEventPtr MouseMoved::make(Button b, int xx, int yy){
  auto p = std::unique_ptr<MouseMoved>(new MouseMoved(b,xx,yy));
  return std::move(p);
}

InputEventPtr MousePressed::make(Button b, int xx, int yy){
  auto p = std::unique_ptr<MousePressed>(new MousePressed(b, xx,yy));
  return std::move(p);
}

InputEventPtr MouseReleased::make(Button b, int xx, int yy){
  auto p = std::unique_ptr<MouseReleased>(new MouseReleased(b, xx,yy));
  return std::move(p);
}

InputEventPtr TextEvent::make(std::string code){
  auto p = std::unique_ptr<TextEvent>(new TextEvent(code));
  return std::move(p);
}

InputEventPtr KeyEvent::make(Kind kind, bool alt, bool shift, bool ctrl, bool system, KeyCode code){
  auto p = std::unique_ptr<KeyEvent>(new KeyEvent(kind, alt, shift, ctrl, system, code));
  return std::move(p);
}
