#include "LayoutParams.hpp"
#include "View.hpp"
void LayoutParams::set(ViewPtr v, int width, int height){
  auto l = static_cast<LayoutParams*>(v->getLayoutParams());
  set(v, Params::EXACT, Params::EXACT);
  l->width.value = width;
  l->height.value = height;
}

void LayoutParams::set(ViewPtr v, Params width, Params height){
  auto l = static_cast<LayoutParams*>(v->getLayoutParams());
  l->width = width;
  l->height = height;
}
