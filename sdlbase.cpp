#include "sdlbase.hpp"
#include "TestGUI.hpp"
#include "KeyCodeConverter.hpp"
#include <SDL2_ttf/SDL_ttf.h>

namespace GUI{
  SDLBase::SDLBase():frameTime(0){

  }
  bool SDLBase::Initialize(){
    //debug_print("Initializing with Width: %d, Height: %d\n", _gui->GetWidth(), _gui->GetHeight());
    debug_expr(_gui->GetWidth());
    debug_expr(_gui->GetHeight());
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0 ){
      fprintf(stderr, "FATAL ERROR! in SDL_INIT_EVERYTHING. %s\n", SDL_GetError());
      return false;
    }
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window =  SDL_CreateWindow(_gui->GetTitle().c_str(),
			       SDL_WINDOWPOS_CENTERED,
			       SDL_WINDOWPOS_CENTERED,
			       _gui->GetWidth(),
			       _gui->GetHeight(),
			       SDL_WINDOW_SHOWN);
    if (!window){
      fprintf(stderr, "FATAL ERROR!. Cannot create Window.");
      return false;
    }

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!ren){
      fprintf(stderr, "FATAL ERROR! in SDL_CreateRenderer. %s\n", SDL_GetError());
      return false;
    }
    //SDL_RenderSetLogicalSize( ren, _gui->GetWidth(), _gui->GetHeight());
    SDL_ClearError();
    //debug_print("Error in SDL_CreateRenderer %s\n",SDL_GetError());
    //SDL_GL_SetSwapInterval(1);
    if(TTF_Init() == -1){
      debug_print("FATAL ERROR!. Cannot initialize TTF.");
      return false;
    }
    glcontext = SDL_GL_CreateContext(window);
    _gui->SetWindow(window);
    _gui->SetRenderer(ren);
    _gui->Initialize();
    //_gui->sdlbase = this;
    return true;

  }

  void SDLBase::MessagePump(){
    debug_print("Into Message Pump ...");
    using U64 =  double;//unsigned long long;
    U64 t = 0;
    const U64 dt = 50;
    const U64 freq = 1000.0/SDL_GetPerformanceFrequency();
    U64 currTime = SDL_GetPerformanceCounter() * freq;
    U64 accumulator = 0;
    is_running = true;

    while (is_running){
      U64 newTime = SDL_GetPerformanceCounter() * freq;
      U64 frameTime = newTime - currTime;
      this->frameTime = frameTime;

      if( frameTime > 250 ) frameTime = 250;
      currTime = newTime;
      accumulator += frameTime; //Add the time previous loop took to acc.
      _gui->UntimedUpdate();
      _gui->SetFrameTime(frameTime);
      int count = 0;
      while(accumulator >= dt){ //consume it in dt steps{
	  count++;
	  _gui->TimedUpdate(dt);
	  t += dt;
	  accumulator -= dt;
	}
      const float alpha = (float)accumulator / dt;

      SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
      SDL_RenderClear(ren);
      _gui->Render(alpha);
      SDL_RenderPresent(ren);
      SDL_Delay(10);
      SDL_Event event;
      while(SDL_PollEvent(&event)){
	HandleEvent(event);
      }
      // if(frameTime < 16.666)
      // 	SDL_Delay(16.666 - frameTime );
    }
  }


void  SDLBase::HandleEvent(SDL_Event& event){
    if (event.type == SDL_QUIT){
      //window->close();
      is_running = false;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN ||
	event.type == SDL_MOUSEBUTTONUP  ){
      SDL_MouseButtonEvent& e = event.button;
      int x = e.x;
      int y = e.y;
      Button button;
      if(e.button == SDL_BUTTON_RIGHT)
	button = Button::RIGHT;
      else if(e.button == SDL_BUTTON_LEFT)
	button = Button::LEFT;
      InputEventPtr ievent;
      if(event.type == SDL_MOUSEBUTTONDOWN){
	ievent = MousePressed::make(button, x, y);
      }else{
	ievent = MouseReleased::make(button, x, y);
      }
      _gui->AddInputEvent(ievent);
    }


    else if (event.type == SDL_MOUSEMOTION){
      int x = event.motion.x;
      int y = event.motion.y;
      Button button;
      auto mp =  MouseMoved::make(button,x,y);
      _gui->AddInputEvent(mp);
    }

    // else if (event.type == sf::Event::Resized){
    //   int width = event.size.width;
    //   int height = event.size.height;
    //   auto eve = WindowsResized::make(width,height);
    //   _gui->AddInputEvent(eve);
    //   auto viewport_width = window->getView().getViewport().width;
    //   auto view_width = window->getView().getSize().x;
    //   sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
    //   window->setView(sf::View(visibleArea));

    //   debug_print("Window resized, viewport %f, view %f\n",viewport_width,view_width);
    // }

    else if(event.type == SDL_TEXTINPUT){
      auto eve = TextEvent::make(event.text.text);
      _gui->AddInputEvent(eve);
    }

    else if (event.type == SDL_KEYDOWN ||
    	     event.type == SDL_KEYUP){
      bool alt = event.key.keysym.mod == KMOD_ALT;
      bool ctrl = event.key.keysym.mod == KMOD_CTRL;
      bool shift = event.key.keysym.mod == KMOD_SHIFT;
      bool system = event.key.keysym.mod == KMOD_GUI;
      KeyCode code = keycodeconvert(event.key.keysym.scancode);
      //debug_print("%s", SDL_GetKeyName(event.key.keysym.scancode));
      KeyEvent::Kind kind;
      if (event.type == SDL_KEYDOWN)
    	kind = KeyEvent::Kind::PRESSED;
      else
    	kind = KeyEvent::Kind::RELEASED;

      auto eve = KeyEvent::make(kind, alt, shift, ctrl, system, code);
      _gui->AddInputEvent(eve);
    }
  }

  SDLBase* SDLBase::Create(GUIBase* gui){
    SDLBase* gb = new SDLBase();
    gb->_gui = gui;

    if(!gb->Initialize()) return nullptr;
    return gb;
  }

  SDLBase::~SDLBase(){
    TTF_Quit();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }


  extern "C" int main(int argc, char* argv[]){
    debug_print("Starting...");
    TestGUI guiTest;
    GUIBase *gui = GUIBase::getInstance();
    if (!gui){
      debug_print("Cannot get gui instance");
      return -1;
    }
    SDLBase* gb = SDLBase::Create(gui);
    if(!gb){
      debug_print("Cannot create sdlbase");
      return -1;
    }
    gb->MessagePump();
    delete gb;
    return 0;
  }

}
