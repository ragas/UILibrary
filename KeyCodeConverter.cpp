#include "KeyCodeConverter.hpp"
KeyCode keycodeconvert(SDL_Scancode key){
  KeyCode code = KeyCode::Unknown;
  if(key == SDL_SCANCODE_UNKNOWN) code = KeyCode::Unknown;
  else if(key == SDL_SCANCODE_A) code = KeyCode::A;
  else if(key == SDL_SCANCODE_B) code = KeyCode::B;
  else if(key == SDL_SCANCODE_C) code = KeyCode::C;
  else if(key == SDL_SCANCODE_D) code = KeyCode::D;
  else if(key == SDL_SCANCODE_E) code = KeyCode::E;
  else if(key == SDL_SCANCODE_F) code = KeyCode::F;
  else if(key == SDL_SCANCODE_G) code = KeyCode::G;
  else if(key == SDL_SCANCODE_H) code = KeyCode::H;
  else if(key == SDL_SCANCODE_I) code = KeyCode::I;
  else if(key == SDL_SCANCODE_J) code = KeyCode::J;
  else if(key == SDL_SCANCODE_K) code = KeyCode::K;
  else if(key == SDL_SCANCODE_L) code = KeyCode::L;
  else if(key == SDL_SCANCODE_M) code = KeyCode::M;
  else if(key == SDL_SCANCODE_N) code = KeyCode::N;
  else if(key == SDL_SCANCODE_O) code = KeyCode::O;
  else if(key == SDL_SCANCODE_P) code = KeyCode::P;
  else if(key == SDL_SCANCODE_Q) code = KeyCode::Q;
  else if(key == SDL_SCANCODE_R) code = KeyCode::R;
  else if(key == SDL_SCANCODE_S) code = KeyCode::S;
  else if(key == SDL_SCANCODE_T) code = KeyCode::T;
  else if(key == SDL_SCANCODE_U) code = KeyCode::U;
  else if(key == SDL_SCANCODE_V) code = KeyCode::V;
  else if(key == SDL_SCANCODE_W) code = KeyCode::W;
  else if(key == SDL_SCANCODE_X) code = KeyCode::X;
  else if(key == SDL_SCANCODE_Y) code = KeyCode::Y;
  else if(key == SDL_SCANCODE_Z) code = KeyCode::Z;
//   else if(key == SDL_SCANCODE_Num0) code = KeyCode::Num0;
//   else if(key == SDL_SCANCODE_Num1) code = KeyCode::Num1;
//   else if(key == SDL_SCANCODE_Num2) code = KeyCode::Num2;
//   else if(key == SDL_SCANCODE_Num3) code = KeyCode::Num3;
//   else if(key == SDL_SCANCODE_Num4) code = KeyCode::Num4;
//   else if(key == SDL_SCANCODE_Num5) code = KeyCode::Num5;
//   else if(key == SDL_SCANCODE_Num6) code = KeyCode::Num6;
//   else if(key == SDL_SCANCODE_Num7) code = KeyCode::Num7;
//   else if(key == SDL_SCANCODE_Num8) code = KeyCode::Num8;
//   else if(key == SDL_SCANCODE_Num9) code = KeyCode::Num9;
//   else if(key == SDL_SCANCODE_Escape) code = KeyCode::Escape;
//   else if(key == SDL_SCANCODE_LControl) code = KeyCode::LControl;
//   else if(key == SDL_SCANCODE_LShift) code = KeyCode::LShift;
//   else if(key == SDL_SCANCODE_LAlt) code = KeyCode::LAlt;
//   else if(key == SDL_SCANCODE_LSystem) code = KeyCode::LSystem;
//   else if(key == SDL_SCANCODE_RControl) code = KeyCode::RControl;
//   else if(key == SDL_SCANCODE_RShift) code = KeyCode::RShift;
//   else if(key == SDL_SCANCODE_RAlt) code = KeyCode::RAlt;
//   else if(key == SDL_SCANCODE_RSystem) code = KeyCode::RSystem;
//   else if(key == SDL_SCANCODE_Menu) code = KeyCode::Menu;
//   else if(key == SDL_SCANCODE_LBracket) code = KeyCode::LBracket;
//   else if(key == SDL_SCANCODE_RBracket) code = KeyCode::RBracket;
//   else if(key == SDL_SCANCODE_SemiColon) code = KeyCode::SemiColon;
//   else if(key == SDL_SCANCODE_ Comma) code = KeyCode:: Comma;
//   else if(key == SDL_SCANCODE_ Period) code = KeyCode:: Period;
//   else if(key == SDL_SCANCODE_ Quote) code = KeyCode:: Quote;
//   else if(key == SDL_SCANCODE_ Slash) code = KeyCode:: Slash;
//   else if(key == SDL_SCANCODE_ BackSlash) code = KeyCode:: BackSlash;
//   else if(key == SDL_SCANCODE_ Tilde) code = KeyCode:: Tilde;
//   else if(key == SDL_SCANCODE_ Equal) code = KeyCode:: Equal;
//   else if(key == SDL_SCANCODE_ Dash) code = KeyCode:: Dash;
  else if(key == SDL_SCANCODE_SPACE) code = KeyCode:: Space;
  else if(key == SDL_SCANCODE_RETURN) code = KeyCode:: Return;
  else if(key == SDL_SCANCODE_BACKSPACE) code = KeyCode::BackSpace;
//   else if(key == SDL_SCANCODE_ Tab) code = KeyCode:: Tab;
//   else if(key == SDL_SCANCODE_ PageUp) code = KeyCode:: PageUp;
//   else if(key == SDL_SCANCODE_ PageDown) code = KeyCode:: PageDown;
//   else if(key == SDL_SCANCODE_ End) code = KeyCode:: End;
//   else if(key == SDL_SCANCODE_ Home) code = KeyCode:: Home;
//   else if(key == SDL_SCANCODE_ Insert) code = KeyCode:: Insert;
  else if(key == SDL_SCANCODE_DELETE) code = KeyCode:: Delete;
//   else if(key == SDL_SCANCODE_ Add) code = KeyCode:: Add;
//   else if(key == SDL_SCANCODE_ Subtract) code = KeyCode:: Subtract;
//   else if(key == SDL_SCANCODE_ Multiply) code = KeyCode:: Multiply;
//   else if(key == SDL_SCANCODE_ Divide) code = KeyCode:: Divide;
  else if(key == SDL_SCANCODE_LEFT) code = KeyCode:: Left;
  else if(key == SDL_SCANCODE_RIGHT) code = KeyCode:: Right;
  else if(key == SDL_SCANCODE_UP) code = KeyCode:: Up;
  else if(key == SDL_SCANCODE_DOWN) code = KeyCode:: Down;
//   else if(key == SDL_SCANCODE_ Numpad0) code = KeyCode:: Numpad0;
//   else if(key == SDL_SCANCODE_ Numpad1) code = KeyCode:: Numpad1;
//   else if(key == SDL_SCANCODE_ Numpad2) code = KeyCode:: Numpad2;
//   else if(key == SDL_SCANCODE_ Numpad3) code = KeyCode:: Numpad3;
//   else if(key == SDL_SCANCODE_ Numpad4) code = KeyCode:: Numpad4;
//   else if(key == SDL_SCANCODE_ Numpad5) code = KeyCode:: Numpad5;
//   else if(key == SDL_SCANCODE_ Numpad6) code = KeyCode:: Numpad6;
//   else if(key == SDL_SCANCODE_ Numpad7) code = KeyCode:: Numpad7;
//   else if(key == SDL_SCANCODE_ Numpad8) code = KeyCode:: Numpad8;
//   else if(key == SDL_SCANCODE_ Numpad9) code = KeyCode:: Numpad9;
//   else if(key == SDL_SCANCODE_ F1) code = KeyCode:: F1;
//   else if(key == SDL_SCANCODE_ F2) code = KeyCode:: F2;
//   else if(key == SDL_SCANCODE_ F3) code = KeyCode:: F3;
//   else if(key == SDL_SCANCODE_ F4) code = KeyCode:: F4;
//   else if(key == SDL_SCANCODE_ F5) code = KeyCode:: F5;
//   else if(key == SDL_SCANCODE_ F6) code = KeyCode:: F6;
//   else if(key == SDL_SCANCODE_ F7) code = KeyCode:: F7;
//   else if(key == SDL_SCANCODE_ F8) code = KeyCode:: F8;
//   else if(key == SDL_SCANCODE_ F9) code = KeyCode:: F9;
//   else if(key == SDL_SCANCODE_ F10) code = KeyCode:: F10;
//   else if(key == SDL_SCANCODE_ F11) code = KeyCode:: F11;
//   else if(key == SDL_SCANCODE_ F12) code = KeyCode:: F12;
//   else if(key == SDL_SCANCODE_ F13) code = KeyCode:: F13;
//   else if(key == SDL_SCANCODE_ F14) code = KeyCode:: F14;
//   else if(key == SDL_SCANCODE_ F15) code = KeyCode:: F15;
//   else if(key == SDL_SCANCODE_ Pause) code = KeyCode:: Pause;

  return code;
}
