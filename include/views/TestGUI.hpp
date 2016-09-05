#include "gui.hpp"
#include "FrameLayout.hpp"
#include "AbsoluteLayout.hpp"
#include "ScrollView.hpp"
#include "TextView.hpp"
#include "LinearLayout.hpp"
#include "MapView.hpp"
#include <geosim.hpp>
#include "utility.hpp"
#include "MapPainter.hpp"

class TestGUI: public GUI::GUIBase{
  struct Page1{
    AbsoluteLayoutPtr fpsDisplay;
    TextViewPtr fps;
  } page1;
  
  FrameLayoutPtr  rootView;
  std::unique_ptr<Canvas> canvas;
  std::unique_ptr<GeoSim> gsim;
  std::unique_ptr<MapPainter> assetManager;
  void InitAllViews();
  void Initialize() override;
  void TimedUpdate(float) override;
  void UntimedUpdate() override;
  void Render(float) override;
};

