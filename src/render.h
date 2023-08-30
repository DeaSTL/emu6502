#include <SDL2/SDL.h>
#include <stdint.h>
#include "cpu.h"
#pragma once


namespace render{


  int init(cpu_t* cpu);
  void draw();
  void eventLoop();
  void destroy();
  void updatePallet();



}
