#include "FrameLayout.hpp"

std::unique_ptr<LayoutParams> FrameLayout::generateDefaultLayoutParams(){
  auto lp = std::unique_ptr<LayoutParams>(new FrameLayoutParams(LayoutParams::DimenType(LayoutParams::Params::WRAP_CONTENT),
								LayoutParams::DimenType(LayoutParams::Params::WRAP_CONTENT)));
  return lp;
}


void FrameLayout::doMeasure(Measure wm, Measure hm){
  measureChildren(wm, hm);
  int maxHt = 0, maxWt = 0;
  for(auto& child : children){
    int childRt = child->measuredWt.value;
    int childBt = child->measuredHt.value;
    maxWt = std::max(childRt, maxWt);
    maxHt = std::max(childBt, maxHt);
  }
  maxWt += mLeftPad + mRightPad;
  maxHt += mTopPad + mBottomPad;

  measuredWt.value = resolveSize(maxWt, wm);
  measuredHt.value = resolveSize(maxHt, hm);
}

void FrameLayout::doLayout(bool , int ,int ,int ,int ){

  for(auto& child : children){
    auto lp = static_cast<FrameLayoutParams*>(child->getLayoutParams());
    int childL = mLeftPad, childT = mTopPad;
    switch(lp->horizontal){
    case(Align::START):
      childL = mLeftPad;
      break;
    case(Align::END):
      childL = right - left - mRightPad - child->measuredWt.value;
      break;
    case(Align::CENTER):
      childL = (right - left)/2 - child->measuredWt.value/2;
      break;
    }

    switch(lp->verticle){
    case(Align::START):
      childT = mTopPad;
      break;
    case(Align::END):
      childT = bottom - top - mBottomPad - child->measuredHt.value;
      break;
    case(Align::CENTER):
      childT = (bottom - top)/2 - child->measuredHt.value/2;
      break;
    }

    child->layout(childL, childT,
		  childL + child->measuredWt.value,
		  childT + child->measuredHt.value);
  }
}

std::unique_ptr<FrameLayout> FrameLayout::make(){
  auto lay = std::make_unique<FrameLayout>();
  return std::move(lay);
}

void FrameLayoutParams::set(ViewPtr v, Align width, Align height){
  auto l = static_cast<FrameLayoutParams*>(v->getLayoutParams());
  l->horizontal = width;
  l->verticle = height;
}

void FrameLayout::add(ViewPtr v, Align width, Align height){
  auto lp = generateDefaultLayoutParams();
  auto lpp = static_cast<FrameLayoutParams*>(lp.get());
  lpp->horizontal = width;
  lpp->verticle = height;
  ViewGroup::addView(v, -1, std::move(lp));
}
