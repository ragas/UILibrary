#include "MapView.hpp"

MapView::~MapView(){
  SDL_DestroyTexture(cacheTexture);
}

void MapView::doDraw(Canvas& c){
  auto dimen = gsim->getConfig().dimen;
  auto tileSize = painter->mainMapTileSize;
  auto localLeft = left;
  auto localTop = top;
  c.getCurrentWorldXY(localLeft, localTop);
  auto const ttop = localTop;
  
  if(cacheTexture != NULL){
    c.clip();
    c.drawTexture(cacheTexture, localLeft, localTop, scrollX, scrollY, dimen*tileSize,
		  dimen*tileSize);
    c.disableClip();
    return;
  }

  cacheTexture = painter->getTemp(dimen*tileSize, dimen*tileSize);
  int xtop = 0, xleft = 0;
  int xxtop =0, xxleft=0;
  for(UShort i  = 0; i<= dimen; ++i){
    for(UShort j = 0; j<=dimen; ++j){
      auto tile = gsim->getTile(Pair(i,j));
      auto sp = painter->getSprite(tile);

      
      //gsim->getTile(Pair(i,j))->generateSubTiles();

      c.drawSprite(sp, cacheTexture, xleft, xtop, tileSize, tileSize);
      // for(UShort x =0; x < 16; ++x){
    //   	for(UShort y =0; y < 16; ++y){
    //   	  auto sp = painter->getSprite(tile, Pair(x,y));
    //   	  c.drawSprite(sp, cacheTexture, xxleft, xxtop, tileSize, tileSize);
    // 	  xxtop += tileSize;
    //   	}
    // 	xxleft += tileSize;
    // 	xxtop = xtop;
    //   }
    //   xtop += tileSize*16;
    //   xxleft = xleft;
      xtop += tileSize;
     }
    xtop = 0;
    xleft += tileSize;
  }
  //c.disableClip();
}

void MapView::doMeasure(Measure wm, Measure hm){
  measuredWt = wm;
  measuredHt = hm;
  auto dimen = gsim->getConfig().dimen;
  auto tileSize = painter->mainMapTileSize;
  measuredWt.value = resolveSize(dimen*tileSize, wm);
  measuredHt.value = resolveSize(dimen*tileSize, hm);
}

void MapView::doLayout(bool , int ,int ,int ,int ){
}

std::unique_ptr<MapView> MapView::make(GeoSim* geosim, MapPainter* painter){
  auto tv = std::make_unique<MapView>();
  tv->gsim = geosim;
  tv->painter = painter;
  tv->cacheTexture = NULL;
  return tv;
}
