#pragma once
#include "View.hpp"
#include "MapPainter.hpp"

class MapView : public View {
  GeoSim* gsim;
  MapPainter* painter;
  SDL_Texture* cacheTexture;
public:
  virtual void doMeasure(Measure, Measure) override;
  virtual void doLayout(bool, int,int,int,int) override;
  virtual void doDraw(Canvas&) override;
  virtual ~MapView();
  static std::unique_ptr<MapView> make(GeoSim*, MapPainter*);
};
using MapViewPtr = std::shared_ptr<MapView>;
