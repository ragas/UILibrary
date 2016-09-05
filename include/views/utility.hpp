#pragma once
#include <iostream>
#define debug_print(fmt)					\
  do {if (DEBUG) std::cout << fmt << std::endl;}while(0)
#define debug_expr(expr) \
  do {if(DEBUG) std::cout << #expr << ":" << expr << std::endl;}while(0)
