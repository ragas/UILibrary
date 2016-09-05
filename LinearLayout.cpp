#include "LinearLayout.hpp"

std::unique_ptr<LayoutParams> LinearLayout::generateDefaultLayoutParams(){
  auto lp = std::unique_ptr<LayoutParams>(new LinearLayoutParams(LayoutParams::DimenType(LayoutParams::Params::WRAP_CONTENT),
								 LayoutParams::DimenType(LayoutParams::Params::WRAP_CONTENT)));
  return lp;
}


void LinearLayout::doMeasure(Measure wm, Measure hm){
  measureChildren(wm,hm);
  int myHt =0, myWt = 0;
  for(auto& child : children){
    int childWt = child->measuredWt.value;
    int childHt = child->measuredHt.value;

    if(!orientation){
      myWt = std::max(childWt, myWt);
      myHt += childHt;
    } else {
      myHt = std::max(childHt, myHt);
      myWt += childWt;
    }
  }
  myWt += mLeftPad + mRightPad;
  myHt += mTopPad + mBottomPad;
  if(children.size() > 0){
    if(!orientation)
      myHt += margin*(children.size() - 1);
    else
      myWt += margin*(children.size() - 1);
  }

  measuredWt.value = resolveSize(myWt, wm);
  measuredHt.value = resolveSize(myHt, hm);
}


void LinearLayout::doLayout(bool, int, int,int,int){
  int currTop = mTopPad;
  int currLeft = mLeftPad;
  for(auto& child : children){
    int childL = currLeft;
    int childT = currTop;
    auto lp = static_cast<LinearLayoutParams*>(child->getLayoutParams());
    switch(lp->alignment){
    case(Align::START):
      break;
    case(Align::END):
      childL = right - left - mRightPad - child->measuredWt.value;
      break;
    case(Align::CENTER):
      childL = (right - left)/2 - child->measuredWt.value/2;
      break;
    }

    child->layout(childL, childT,
		  childL + child->measuredWt.value,
		  childT + child->measuredHt.value);
    if(!orientation)
      currTop += child->measuredHt.value + margin;
    else
      currLeft += child->measuredWt.value + margin;
  }
}


std::unique_ptr<LinearLayout> LinearLayout::make(){
  auto lay = std::make_unique<LinearLayout>();
  return std::move(lay);
}

void LinearLayoutParams::set(ViewPtr v, Align align){
  auto l = static_cast<LinearLayoutParams*>(v->getLayoutParams());
  l->alignment = align;
}

void LinearLayout::add(ViewPtr v, Align align){
  auto lp = generateDefaultLayoutParams();
  auto lpp = static_cast<LinearLayoutParams*>(lp.get());
  lpp->alignment = align;
  ViewGroup::addView(v, -1, std::move(lp));
}
