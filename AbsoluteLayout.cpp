#include "AbsoluteLayout.hpp"

std::unique_ptr<LayoutParams> AbsoluteLayout::generateDefaultLayoutParams(){
  auto lp = std::unique_ptr<LayoutParams>(new AbsoluteLayoutParams(LayoutParams::DimenType(LayoutParams::Params::WRAP_CONTENT),
								   LayoutParams::DimenType(LayoutParams::Params::WRAP_CONTENT)));
  return lp;
}

void AbsoluteLayout::doMeasure(Measure wm, Measure hm){
  measureChildren(wm, hm);
  int maxHt = 0, maxWt = 0;
  for(auto& child : children){
    auto lp = static_cast<AbsoluteLayoutParams*>(child->getLayoutParams());
    int childRt = lp->position_x + child->measuredWt.value;
    int childBt = lp->position_y + child->measuredHt.value;
    maxWt = std::max(childRt, maxWt);
    maxHt = std::max(childBt, maxHt);
  }
  maxWt += mLeftPad + mRightPad;
  maxHt += mTopPad + mBottomPad;

  measuredWt.value = resolveSize(maxWt, wm);
  measuredHt.value = resolveSize(maxHt, hm);
}

void AbsoluteLayout::doLayout(bool , int ,int ,int ,int ){

  for(auto& child : children){
    auto lp = static_cast<AbsoluteLayoutParams*>(child->getLayoutParams());
    int childL = mLeftPad + lp->position_x;
    int childT = mTopPad + lp->position_y;

    child->layout(childL, childT,
		  childL + child->measuredWt.value,
		  childT + child->measuredHt.value);
  }
}

void AbsoluteLayoutParams::set(ViewPtr v, int position_x, int position_y){
  auto l = static_cast<AbsoluteLayoutParams*>(v->getLayoutParams());
  l->position_x = position_x;
  l->position_y = position_y;
}

std::unique_ptr<AbsoluteLayout> AbsoluteLayout::make(){
  auto lay = std::make_unique<AbsoluteLayout>();
  return std::move(lay);
}
