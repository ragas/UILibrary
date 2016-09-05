#include "TextView.hpp"
#include <cmath>
#include "Assets.hpp"

void TextView::doMeasure(Measure wm, Measure hm){
  measuredWt = wm;
  measuredHt = hm;

  int iW, iH;

  painter->getTextSize(text, iW,iH);
  int ht = iH;
  int wt = iW;

  ht += mTopPad + mBottomPad;
  wt += mLeftPad + mRightPad;

  measuredWt.value = resolveSize(wt, wm);
  measuredHt.value = resolveSize(ht, hm);
}

void TextView::doLayout(bool , int ,int ,int ,int ){
}


void TextView::doDraw(Canvas& c){
  int x,y;
  c.getCurrentWorldXY(x,y);
  c.drawText(text, x, y, getWidth(), getHeight(),textColor,painter);
}

bool TextView::dispatchTextEnteredEvent(TextEvent* tevent){
  auto code = tevent->code;

  if(code == "\b"){
    if(text.size() > 0)
      text.pop_back();
  }
  else
    text += code;
  return true;
}

bool TextView::dispatchKeyEvent(KeyEvent* event){
  if(event->kind == KeyEvent::Kind::PRESSED)
    if(event->code == KeyCode::Down)
      requestUnFocus(FocusDirection::DOWN);
    else if (event->code == KeyCode::Up)
      requestUnFocus(FocusDirection::UP);
    else if (event->code == KeyCode::BackSpace)
      if(text.size()>0) text.pop_back();

  return true;
}

std::unique_ptr<TextView> TextView::make(std::string data){
  auto tv = std::make_unique<TextView>();
  tv->setText(data);
  return tv;
}

