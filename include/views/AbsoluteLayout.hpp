#pragma  once
#include "ViewGroup.hpp"

class AbsoluteLayout : public ViewGroup {
protected:
  //virtual void drawChildren(Canvas&) override;
  virtual void doLayout(bool, int, int,int,int) override;
public:
  struct AbsoluteLayoutParams : LayoutParams{
    inline AbsoluteLayoutParams(DimenType w, DimenType h):LayoutParams(w,h), position_x(0),position_y(0){}
    int position_x, position_y;
    static void set(ViewPtr, int,int);
  };
  inline AbsoluteLayout(){};
  virtual std::unique_ptr<LayoutParams> generateDefaultLayoutParams() final;
  virtual void doMeasure(Measure, Measure) override;
  static std::unique_ptr<AbsoluteLayout> make();
};

using AbsoluteLayoutPtr = std::shared_ptr<AbsoluteLayout>;
using AbsoluteLayoutParams = AbsoluteLayout::AbsoluteLayoutParams;
