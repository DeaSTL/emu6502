#include <cstdint>
#include "cpu.h"
#include "instructions.h"

namespace emuops {
  void load_step(uint8_t* memory, uint8_t* rom, struct cpu_t *cpu, void (*tick)()){
    switch (rom[cpu->pc]) {
      case IN_LDA_IMM: // Load accumulator from immediate
        tick();
        cpu->pc++;
        tick();
        cpu->acc = rom[cpu->pc];
        break;
      case IN_LDX_IMM: // Load X from immediate
        tick();
        cpu->pc++;
        tick();
        cpu->x = rom[cpu->pc];
        break;
      case IN_LDX_ZPG: // Load X from zero page
        cpu->status_message = "Loading X from zero page"; 
        tick();
        cpu->pc++;
        tick();
        cpu->x = memory[rom[cpu->pc]];
        break;
      case IN_LDY_IMM: // Load Y from immediate
        tick();
        cpu->pc++;
        tick();
        cpu->y = rom[cpu->pc];
        break;
      case IN_LDA_ZPG: // Load accumulator from zero page
        tick();
        cpu->pc++;
        tick();
        cpu->acc = memory[rom[cpu->pc]];
        break;
      case IN_LDY_ZPG: // Load Y from zero page
        tick();
        cpu->pc++;
        tick();
        cpu->y = memory[rom[cpu->pc]];
        break;
    }
  }
}
