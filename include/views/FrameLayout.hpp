#pragma once
#include "ViewGroup.hpp"

class FrameLayout : public ViewGroup {
protected:
  virtual void doLayout(bool, int, int,int,int) override;
public:
  enum class Align{START, END, CENTER};
  struct FrameLayoutParams : LayoutParams{
    inline FrameLayoutParams(DimenType w, DimenType h):LayoutParams(w,h), verticle(Align::START), horizontal(Align::START){}
    Align verticle, horizontal;
    static void set(ViewPtr, Align, Align);
  };
  inline FrameLayout(){};
  virtual std::unique_ptr<LayoutParams> generateDefaultLayoutParams() final;
  virtual void doMeasure(Measure, Measure) override;
  static std::unique_ptr<FrameLayout> make();
  void add(ViewPtr, Align, Align);
};

using FrameLayoutPtr = std::shared_ptr<FrameLayout>;
using FrameLayoutParams = FrameLayout::FrameLayoutParams;
