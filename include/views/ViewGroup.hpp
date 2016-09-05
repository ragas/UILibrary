#pragma once
#include "View.hpp"
#include "ViewParent.hpp"

class ViewGroup : public View, public ViewParent {  
protected:
  std::vector<ViewPtr> children;
  inline void addChild(ViewPtr v, int pos, std::unique_ptr<LayoutParams> );
  void measureChild(View* v, View::Measure w, View::Measure h);
  View::Measure calcChildMeasureSpec(View::Measure, int, LayoutParams::DimenType );
  void measureChildren(View::Measure wm, View::Measure hm);
  virtual void drawChildren(Canvas& c) override;
  View* focusedChild;
  View* targetChild;
  std::function<bool(View*, KeyEvent*)> onKeyEventListener;
public:
  inline ViewGroup(){focusable=false; focusedChild = nullptr; targetChild = nullptr;};
  //void addViewVal(ViewPtr);
  void addView(ViewPtr );
  void addView(ViewPtr v, int );
  void addView(ViewPtr v, int pos, std::unique_ptr<LayoutParams> ); 
  void delView(ViewPtr );

  bool dispatchMouseEvent(MouseEvent*) override;
  void interceptOnKey(std::function<bool(View*, KeyEvent*)>);

  void childFocused(View*, View*) override;
  bool requestFocus(FocusDirection) override;
  virtual void childUnFocused(View*, FocusDirection) override;
  void unfocus() override;
  bool dispatchTextEnteredEvent(TextEvent*) override;
  bool dispatchKeyEvent(KeyEvent*) override;
  virtual std::unique_ptr<LayoutParams> generateDefaultLayoutParams() = 0;  
  virtual void doLayout(bool, int,int,int,int) override = 0;    
};
