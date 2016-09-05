#include "TestGUI.hpp"
#include <string>


void TestGUI::Initialize(){
  debug_print("Initializing GUI....\n");
  canvas.reset(new Canvas(renderer, GetWidth(), GetHeight()));
  assetManager.reset(new MapPainter());
  assetManager->setRenderer(renderer);
  assetManager->mainMapTileSize = 12;
  View::painter = assetManager.get();

  assetManager->init();
  InitAllViews();

  auto gsm =  GeoSimConfig(64, "ABCD",
			   512, 1,
			   100, 1,
			   100, 1);
  gsm.shoreLevel = 75;
  gsim.reset(new GeoSim(gsm));
}

void TestGUI::TimedUpdate(float ){

}

void TestGUI::UntimedUpdate(){

  while (!inputEventQ.empty()){
    auto event = std::move(inputEventQ.front());
    inputEventQ.pop();
    auto&& etype = event->getEventType();
    if(etype == WindowsResized::type){
      View::Measure hm, wm;
      hm.spec = View::Measure::EXACT;
      wm.spec = View::Measure::EXACT;
      hm.value = GetHeight();
      wm.value = GetWidth();

      rootView->measure(wm,hm);
      rootView->layout(0, 0, GetWidth(), GetHeight());
    }else {
      rootView->dispatchEvent(event.get());
    }
  }
  page1.fps->setText(std::to_string(1000/frameTime));

  View::Measure hm, wm;
  hm.spec = View::Measure::EXACT;
  wm.spec = View::Measure::EXACT;
  hm.value = GetHeight();
  wm.value = GetWidth();

  rootView->measure(wm,hm);
  rootView->layout(0, 0, GetWidth(), GetHeight());
}

void TestGUI::Render(float){
  rootView->draw(*canvas);
}


void TestGUI::InitAllViews(){
  FrameLayoutPtr frontPage = FrameLayout::make();
  page1.fpsDisplay = AbsoluteLayout::make();
  page1.fps = TextView::make("0");

  TextViewPtr topBanner = TextView::make("BANNER");
  topBanner->setFontsize(25);

  TextViewPtr bottomBanner = TextView::make("INFOINFO");
  bottomBanner->setFontsize(14);

  LinearLayoutPtr menu = LinearLayout::make();

  TextViewPtr oneText = TextView::make("Start");
  TextViewPtr twoText = TextView::make("BLANK");
  TextViewPtr threeText = TextView::make("Exit");

  auto textBrighten = [](View* v, bool focused){
    auto textView = static_cast<TextView*>(v);
    if(focused)
      textView->setTextColor(Color(255,0,0));
    else
      textView->setTextColor(Color(255,255,255));
  };
  oneText->doFocusChanged(textBrighten);
  twoText->doFocusChanged(textBrighten);
  threeText->doFocusChanged(textBrighten);

  auto nextPage = [&](View* ){
    auto f = [this](){
      double var_rain = 90;
      double var_temp = 20;
      double var_elev = 1000;
      int count = 1000;
      while (count--){
	//gsim->resetAll();
	gsim->MakeElev(var_elev,1.6,512, 1,true);
	gsim->MakeRain(var_rain,1.5,100,1);
	gsim->MakeTemp(var_temp,1.9,100,1);
	if(gsim->CheckIfOK() == Failure::SUCCESS)
	  break;
      }
      //debug_expr(count);
      //auto dimen = gsim->getConfig().dimen;
      //gsim->CreateEdges();
      // count = 1000;
      // while(count--)
      // 	gsim->DropErosion();

    };
    f();
    MapViewPtr mp = MapView::make(gsim.get(),assetManager.get());
    mp->doOnKey([this,f](View*, KeyEvent* e){
	if(e->kind == KeyEvent::Kind::PRESSED &&
	   e->code == KeyCode::Space){
	  f();
	  return true;
	}
	return false;
      });
    ScrollViewPtr sv = ScrollView::make(mp);


    FrameLayoutPtr fview = FrameLayout::make(); 
    fview->add(sv, FrameLayout::Align::CENTER, FrameLayout::Align::CENTER);
    sv->getLayoutParams()->width.param =
    sv->getLayoutParams()->height.param = LayoutParams::Params::EXACT;
    sv->getLayoutParams()->width.value =
    sv->getLayoutParams()->height.value= 600;
    fview->add(page1.fpsDisplay, FrameLayout::Align::START, FrameLayout::Align::START);
    mp->requestFocus(FocusDirection::DOWN);
    rootView = fview;
  };
  oneText->doOnClick(nextPage);

  menu->add(oneText,   LinearLayout::Align::CENTER);
  menu->add(twoText,   LinearLayout::Align::CENTER);
  menu->add(threeText, LinearLayout::Align::CENTER);

  frontPage->add(topBanner, FrameLayout::Align::CENTER, FrameLayout::Align::START);
  frontPage->add(bottomBanner, FrameLayout::Align::CENTER, FrameLayout::Align::END);
  frontPage->add(menu, FrameLayout::Align::CENTER, FrameLayout::Align::CENTER);
  frontPage->add(page1.fpsDisplay, FrameLayout::Align::START, FrameLayout::Align::START);
  page1.fpsDisplay->addView(page1.fps);
  rootView = frontPage;
  oneText->requestFocus(FocusDirection::DOWN);
}
