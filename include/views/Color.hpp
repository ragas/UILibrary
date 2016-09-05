#pragma once
struct Color{
  short r,g,b,a;
  Color():r(0),g(0),b(0),a(255){}
  Color(short red, short green, short blue):r(red), g(green), b(blue),a(255){}
  Color(short red, short green, short blue, short alpha):r(red), g(green), b(blue), a(alpha){}
};
