#include "ScrollView.hpp"
#include "TextView.hpp"

ScrollView::ScrollView(ViewPtr t){
  target = t.get();
  TextViewPtr uparrow = TextView::make("^");
  uparrow->setFontsize(10);
  TextViewPtr downarrow = TextView::make("v");
  downarrow->setFontsize(10);
  addView(t);
  addView(uparrow);
  addView(downarrow);
  singleStep = 5;
  mRightPad = 10;
  totalLength = target->getWidth();
  LayoutParams::set(uparrow, 10, 10);
  LayoutParams::set(downarrow, 10, 10);
  // maxScrollX = totalLength - getWidth();
  // maxScrollY = target->getHeight() - getHeight();
  uparrow->doOnClick([this](View*){
      target->scrollBy(0,-singleStep);
    });

  downarrow->doOnClick([this](View*){
      target->scrollBy(0,singleStep);
    });

  this->interceptOnKey([this](View*, KeyEvent* event){
      if(event->code == KeyCode::Up)
	if(target->getScrollY() > 0)
	target->scrollBy(0,-singleStep);
      if(event->code == KeyCode::Down)
	if(maxChildY - target->getHeight() - target->getScrollY() > 0)
	  target->scrollBy(0,singleStep);
      if(event->code == KeyCode::Left)
	if(target->getScrollX() > 0)
	  target->scrollBy(-singleStep,0);
      if(event->code == KeyCode::Right){
	if(maxChildX - target->getWidth() - target->getScrollX() > 0)
	  target->scrollBy(singleStep,0);
      }
      else
	return false;
      return true;
    });
  this->uparrow = uparrow.get();
  this->downarrow = downarrow.get();
}

std::unique_ptr<LayoutParams> ScrollView::generateDefaultLayoutParams(){
  auto lp = std::unique_ptr<LayoutParams>(new LayoutParams(LayoutParams::DimenType(LayoutParams::Params::MATCH_PARENT),
							   LayoutParams::DimenType(LayoutParams::Params::MATCH_PARENT)));
  return lp;
}


void ScrollView::doMeasure(Measure wm, Measure hm){
  /**
     First measure what is the maximum the target view wants to be.
     Save it for scrolling limits detection.
     Then do the normal measurements
   */
  Measure any;
  any.spec = Measure::ANY;  
  measureChild(target,any, any);
  maxChildX = target->getMeasuredWidth();
  maxChildY = target->getMeasuredHeight();
  measureChildren(wm, hm);
  int maxWt = target->measuredWt.value + uparrow->measuredWt.value;
  int maxHt = target->measuredHt.value;

  maxWt += mLeftPad + mRightPad;
  maxHt += mTopPad + mBottomPad;

  measuredWt.value = resolveSize(maxWt, wm);
  measuredHt.value = resolveSize(maxHt, hm);
}

void ScrollView::doLayout(bool , int ,int ,int ,int ){
  int childL = mLeftPad;
  int childT = mTopPad;
  auto child = target;
  child->layout(childL, childT,
		 childL + child->measuredWt.value,
		 childT + child->measuredHt.value);


  child = uparrow;
  childL = right - left - child->measuredWt.value;
  child->layout(childL, childT,
		 childL + child->measuredWt.value,
		 childT + child->measuredHt.value);

  child = downarrow;
  childT = bottom -top - child->measuredHt.value;
  child->layout(childL, childT,
		 childL + child->measuredWt.value,
		 childT + child->measuredHt.value);

}


std::unique_ptr<ScrollView> ScrollView::make(ViewPtr v){
  auto tv = std::make_unique<ScrollView>(v);
  return tv;
}
