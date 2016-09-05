#pragma once
#include <memory>
#include "Canvas.hpp"
#include "LayoutParams.hpp"
#include "InputEvents.hpp"
#include "ViewParent.hpp"
#include "MapPainter.hpp"
#include <functional>
#include <vector>
#include <cstdlib>

class View {

private:
  void drawScrollbars(Canvas&);
  void drawInternal(Canvas&);
  void setFrame(int, int, int, int);
  static long id_;
  long id;

  std::function<void(View*)> onClickListener;
  std::function<void(View*, bool)> onFocusChangeListener;
  std::function<bool(View*, KeyEvent*)> onKeyEventListener;
  std::function<bool(View*, MouseEvent*)> onMouseEventListener;
protected:
  friend class ViewGroup;
  //friend class ViewParent;
  virtual void drawChildren(Canvas&);
  int top, left, right, bottom;
  int scrollX, scrollY;
  std::unique_ptr<LayoutParams> layoutParams;
  int mLeftPad, mRightPad, mTopPad, mBottomPad;
  bool focused, enabled, visible, focusable;
  bool mousePressed;
  ViewParent* parent;

public:
  static MapPainter* painter;
  struct Measure{
    enum {ANY, MAX, EXACT} spec;
    int value;
  };
  Measure measuredWt, measuredHt;
  bool valid;  

protected:
  int resolveSize(int, Measure);
  virtual void doDraw(Canvas&);
  virtual void doMeasure(Measure, Measure);
  virtual void doLayout(bool, int,int,int,int);

public:

  View();
  inline int getID() const{return id;}
  inline bool isFocused() const {return focused;}
  inline bool isEnabled() const {return enabled;}
  inline bool isVisible() const {return visible;}

  virtual bool requestFocus(FocusDirection dir = FocusDirection::DOWN);
  virtual bool requestUnFocus(FocusDirection dir = FocusDirection::DOWN);  
  virtual void unfocus();
  int getWidth() const;
  int getHeight() const;
  void scrollBy(int, int);
  int getScrollX() const;
  int getScrollY() const;
  
  void draw(Canvas&);
  void measure(Measure, Measure);
  int getMeasuredHeight() const;
  int getMeasuredWidth() const;
  void layout(int,int,int,int);
  void setLayoutParams(std::unique_ptr<LayoutParams> lp);
  LayoutParams* getLayoutParams();

  virtual bool dispatchEvent(InputEvent*);
  virtual bool dispatchMouseEvent(MouseEvent*);
  virtual bool dispatchTextEnteredEvent(TextEvent* );
  virtual bool dispatchKeyEvent(KeyEvent* ev);
  
  void doOnClick(std::function<void(View*)>);
  void doFocusChanged(std::function<void(View*, bool)>);
  void doOnKey(std::function<bool(View*, KeyEvent*)>);
  void doOnMouse(std::function<bool(View*, MouseEvent*)>);
  virtual ~View(){}
};

using ViewPtr = std::shared_ptr<View>;
