#pragma once
#include "cpu.h"
#include <stdint.h>

namespace emuops {
  void math_step(uint8_t* memory, uint8_t* rom, struct cpu_t *cpu,void (*tick)());
  void compare_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)());
  void branch_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)());
  void load_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)());
  void store_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)());
  void flag_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)());
  void misc_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)());
  void memory_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)());
}







