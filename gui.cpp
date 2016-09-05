#include "gui.hpp"

namespace GUI {
  static GUIBase* __gui;

  GUIBase::GUIBase(void):
    title("GUIBase"), width(800), height(640){
    __gui = this;
  }

  GUIBase::~GUIBase(void){}

  GUIBase* GUIBase::getInstance(){
    return __gui;
  }

  void GUIBase::Initialize(){}
  void GUIBase::MainLoop(){}

  void GUIBase::AddInputEvent(InputEventPtr& event){
    inputEventQ.push(std::move(event));
  }

  void GUIBase::SetFrameTime(float dtime){
    frameTime=dtime;
  }
}
