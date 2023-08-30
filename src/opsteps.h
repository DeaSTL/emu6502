#pragma once
#include "cpu.h"
#include <stdint.h>

namespace emuops {
  int math_step(uint8_t* memory, uint8_t* rom, cpu_t *cpu);
  int compare_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu);
  int branch_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu);
  int load_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu);
  int store_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu);
  int flag_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu);
  int misc_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu);
  int memory_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu);
}







