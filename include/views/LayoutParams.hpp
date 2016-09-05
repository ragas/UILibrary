#pragma once
#include <memory>
class View;

enum class FocusDirection{DOWN, LEFT, UP, RIGHT};
struct LayoutParams {
  enum class Params {MATCH_PARENT, WRAP_CONTENT, EXACT} ;
  struct DimenType {
    Params param;
    int value;
    inline DimenType(Params p):param(p){}
  } width, height;

  inline LayoutParams(DimenType w, DimenType h):width(w), height(h){
  }
  static void set(std::shared_ptr<View>, int , int );
  static void set(std::shared_ptr<View>, Params, Params);
};

using LayoutParamsPtr = std::unique_ptr<LayoutParams>;
