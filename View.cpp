#include "View.hpp"
#include "ViewParent.hpp"

long View::id_ = 0;
MapPainter* View::painter = nullptr;
View::View():id(id_++),
	     scrollX(0), scrollY(0),
	     mLeftPad(0), mRightPad(0), mTopPad(0), mBottomPad(0),
	     focused(false), enabled(true), visible(true), focusable(true), mousePressed(false),
	     parent(nullptr)
{

}


void View::doMeasure(Measure wm, Measure hm){
  measuredWt = wm;
  measuredHt = hm;

  int wt = std::abs(right-left);
  int ht = std::abs(top-bottom);
  measuredWt.value = resolveSize(wt, wm);
  measuredHt.value = resolveSize(ht, hm);
}

int View::getMeasuredHeight() const{
  return measuredHt.value;
}

int View::getMeasuredWidth() const{
  return measuredWt.value;
}

void View::scrollBy(int x, int y){
  scrollX += x;
  scrollY += y;
}

int View::getScrollX() const{
  return scrollX;
}

int View::getScrollY() const{
  return scrollY;
}

void View::setLayoutParams(std::unique_ptr<LayoutParams> lp){
  layoutParams = std::move(lp);
}

LayoutParams* View::getLayoutParams(){
  return layoutParams.get();
}

void View::doLayout(bool, int ,int ,int ,int ){
}

int View::resolveSize(int s, Measure spec){
  /**
     Resolev the size and measure spec, which has a size and a specifications of type.
     ANY : whatever this view wants to be
     MAX : whatever UPTO this maximum
     EXACT : exactly this.
   */
  if(spec.spec == Measure::ANY){
    return s;
  }
  if(spec.spec == Measure::MAX){
    return std::min(s, spec.value);
  }
  if(spec.spec == Measure::EXACT){
    return spec.value;
  }
  return s;
}


void View::doDraw(Canvas& ){
}

void View::drawInternal(Canvas& c){
  int x,y;
  c.getCurrentWorldXY(x,y);
  c.drawRect(x, y, getWidth(), getHeight());
}

void View::drawScrollbars(Canvas& ){

}


void View::draw(Canvas& c){
  /**
     Drawing Sequence
     1. First save the canvas matrix
     2. Then translate by correct amount wrt paretn, 
     3. Then draw internal stuff (debugging)
     4. Then CLIP. This is must so that children do not draw beyond
     given boundry,
     5. Then tranlate by scrolling amount (if any)
     6.Draw self
     7.Draw children
     8.Draw decorators
  */
  c.save();
  c.translate(left,top);
  c.clip(left,top,right,bottom);
  drawInternal(c);
  c.translate(-scrollX,-scrollY);
  doDraw(c);
  drawChildren(c);
  drawScrollbars(c);
  c.restore();
}

void View::drawChildren(Canvas&){
}


void View::layout(int left, int top, int right, int bottom){
  setFrame(left, top, right, bottom);
  doLayout(true, left,top,right,bottom);
}

void View::setFrame(int l, int t, int r, int b){
  left = l;
  top = t;
  right = r;
  bottom = b;
}

void View::measure(Measure wm, Measure hm){
  doMeasure(wm, hm);
}

bool View::requestFocus(FocusDirection dir){

  if(!focusable || !visible){
    return false;
  }
  if(!focused){
    focused = true;

    if(parent != nullptr){
      parent->childFocused(this,this);
    }

    if(onFocusChangeListener != nullptr)
      onFocusChangeListener(this,focused);
  }
  return true;
}


bool View::requestUnFocus(FocusDirection dir){
  if(parent != nullptr){
    parent->childUnFocused(this, dir);
    return true;
  }
  return false;
}

bool View::dispatchEvent(InputEvent* event){
  /**
     Event dispatcher, casts to correct type and reroutes
     to other functions
   */
  auto&& eventType = event->getEventType();
  if(eventType == MousePressed::type ||
     eventType == MouseReleased::type ||
     eventType == MouseMoved::type
     ){

    MouseEvent* ev = static_cast<MouseEvent*>(event);
    dispatchMouseEvent(ev);
  }else if(eventType == TextEvent::type){
    TextEvent* tv = static_cast<TextEvent*>(event);
    dispatchTextEnteredEvent(tv);
  }else if (eventType == KeyEvent::type){
    KeyEvent* ev = static_cast<KeyEvent*>(event);
    dispatchKeyEvent(ev);
  }
  return true;
}

bool View::dispatchKeyEvent(KeyEvent* event){
  if(onKeyEventListener != nullptr)
    if(onKeyEventListener(this, event))
       return true;
  return true;
}

bool View::dispatchMouseEvent(MouseEvent* event){
  auto&& eventType = event->getEventType();

  //If have a mouse listner execute it
  if(onMouseEventListener != nullptr)
    if(onMouseEventListener(this, event))
      return true;

  //Set the focus and execute onClick listener
  if(eventType == MousePressed::type){
    mousePressed = true;
  }else if (eventType == MouseReleased::type){
    bool focustaken = false;
    if(!focused){
      //If we were not focused then take the focus, this
      //makes previous focused view go un-focused.
      focustaken = requestFocus();
    }
    if(mousePressed)
      if(onClickListener != nullptr)
	onClickListener(this);
    mousePressed = false;
  }else if (eventType == MouseMoved::type){
    int x = event->x;
    int y = event->y;

    if(x < 0 || y < 0 || x > std::abs(left-right) || y > std::abs(top-bottom))
      mousePressed = false;
  }
  return true;
}

bool View::dispatchTextEnteredEvent(TextEvent* tevent){
  return true;
}

void View::unfocus(){
  mousePressed=false;
  focused=false;
  if(onFocusChangeListener != nullptr)
    onFocusChangeListener(this,focused);
}

void View::doOnClick(std::function<void(View*)> func){
  onClickListener = func;
}

void View::doFocusChanged(std::function<void(View*, bool)> func){
  onFocusChangeListener = func;
}

void View::doOnKey(std::function<bool(View*, KeyEvent*)> func){
  onKeyEventListener = func;
}
void View::doOnMouse(std::function<bool(View*, MouseEvent*)> func){
  onMouseEventListener = func;
}

int View::getWidth() const{
  return std::abs(left-right);
}

int View::getHeight() const{
  return std::abs(top-bottom);
}
