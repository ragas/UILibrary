#pragma once
#include "View.hpp"
#include "Color.hpp"
#include <string>

class TextView : public View {
  std::string text;
  Color textColor;
  int fontsize;
  
public:
SDL_Texture *texture;
  inline TextView():View(){
    //mLeftPad = mRightPad = mTopPad = mBottomPad = 5;
    textColor = Color(255,255,255,255);
    fontsize = 14;
  }
  inline void setText(std::string& t){text = t;}
  inline void setText(std::string&& t){text = t;}
  inline void setTextColor(Color c){textColor = c;}
  inline void setFontsize(unsigned short s){fontsize = s;}
  std::string& getText(){return text;}
  bool dispatchTextEnteredEvent(TextEvent* tevent) override;
  bool dispatchKeyEvent(KeyEvent*) override;
  virtual void doMeasure(Measure, Measure) override;
  virtual void doLayout(bool, int,int,int,int) override;
  virtual void doDraw(Canvas&) override;

  static std::unique_ptr<TextView> make(std::string);
};

using TextViewPtr = std::shared_ptr<TextView>;
