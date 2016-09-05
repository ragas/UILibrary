#pragma once
#include "LayoutParams.hpp"
class View;
struct ViewParent {
  virtual void childFocused(View*, View*) = 0;
  virtual void childUnFocused(View*, FocusDirection) = 0;
  virtual ~ViewParent(){};
};
