
#pragma once
#include <memory>
#include <string>
#include "KeyCodeConverter.hpp"
struct InputEvent {
  virtual int getEventType() = 0;
  virtual ~InputEvent() {}
protected:
  InputEvent(){};
};

using InputEventPtr = std::unique_ptr<InputEvent>;
enum class Button {LEFT,RIGHT};

struct MouseEvent : public InputEvent{
  Button button;
  int x,y;
  inline MouseEvent(Button b,int xx,int yy):button(b), x(xx), y(yy){}
};

struct MousePressed : public MouseEvent{
  static const int type;
  inline virtual int getEventType(){return type;}
  static InputEventPtr make(Button,int,int);
private:
  MousePressed(Button, int, int);
};

struct MouseReleased : public MouseEvent{
  static const int type;
  inline virtual int getEventType(){return type;}
  static InputEventPtr make(Button,int,int);
private:
  MouseReleased(Button, int, int);
};

struct MouseMoved : public MouseEvent{
  static const int type;
  inline virtual int getEventType(){return type;} 
  static InputEventPtr make(Button,int,int);
private:
  MouseMoved(Button, int, int);
  
};


struct KeyEvent : public InputEvent{
  enum class Kind {PRESSED, RELEASED};
  Kind kind;
  bool alt,shift,ctrl,system;
  KeyCode code;
  static const int type;
  inline virtual int getEventType(){return type;}
  static InputEventPtr make(Kind, bool, bool, bool,bool,KeyCode);
private:
  KeyEvent(Kind, bool, bool, bool,bool,KeyCode);

};

struct TextEvent : public InputEvent{
  std::string code;
  static const int type;
  inline virtual int getEventType(){return type;}
  static InputEventPtr make(std::string);
private:
  TextEvent(std::string);
};

struct WindowsResized:public InputEvent{
  static const int type;
  inline virtual int getEventType(){return type;}
  int width,height;
  static InputEventPtr make(int,int);
private:
  WindowsResized(int,int);
};
