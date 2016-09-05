#pragma once
#include "AbsoluteLayout.hpp"

class ScrollView : public ViewGroup {
  int totalLength;
  int pageStep;
  int singleStep;

  int maxChildX;
  int maxChildY;
  
  View* target;
  View* uparrow;
  View* downarrow;

protected:
  virtual void doLayout(bool, int, int,int,int) override;
public:
  ScrollView(ViewPtr);
  virtual std::unique_ptr<LayoutParams> generateDefaultLayoutParams() final;
  virtual void doMeasure(Measure, Measure) override;
  static std::unique_ptr<ScrollView> make(ViewPtr);
};


using ScrollViewPtr = std::shared_ptr<ScrollView>;
