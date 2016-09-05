#pragma once
#include "ViewGroup.hpp"

class LinearLayout : public ViewGroup{
  protected:
  virtual void doLayout(bool, int, int,int,int) override;
  bool orientation;
  int margin;
public:
  enum class Align{START, END, CENTER};
  struct LinearLayoutParams : LayoutParams{
    inline LinearLayoutParams(DimenType w, DimenType h):LayoutParams(w,h), alignment(Align::START){}
    Align alignment;
    static void set(ViewPtr, Align);
  };
  inline LinearLayout():orientation(false),margin(5){};
  virtual std::unique_ptr<LayoutParams> generateDefaultLayoutParams() final;
  virtual void doMeasure(Measure, Measure) override;
  static std::unique_ptr<LinearLayout> make();
  void add(ViewPtr, Align);
};


using LinearLayoutPtr = std::shared_ptr<LinearLayout>;
using LinearLayoutParams = LinearLayout::LinearLayoutParams;
