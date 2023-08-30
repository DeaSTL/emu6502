#include <cstdint>
#include "cpu.h"
#include "instructions.h"

namespace emuops {
  int load_step(uint8_t* memory, uint8_t* rom, cpu_t *cpu){
    switch (rom[cpu->pc]) {
      case IN_LDA_IMM: // Load accumulator from immediate
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc = rom[cpu->pc];
        return 1;
        break;
      case IN_LDX_IMM: // Load X from immediate
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->x = rom[cpu->pc];
        return 1;
        break;
      case IN_LDX_ZPG: // Load X from zero page
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->x = memory[rom[cpu->pc]];
        return 1;
        break;
      case IN_LDY_IMM: // Load Y from immediate
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->y = rom[cpu->pc];
        return 1;
        break;
      case IN_LDA_ZPG: // Load accumulator from zero page
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc = memory[rom[cpu->pc]];
        return 1;
        break;
      case IN_LDY_ZPG: // Load Y from zero page
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->y = memory[rom[cpu->pc]];
        return 1;
        break;
      case IN_LDA_ABS: // Load accumulator from absolute
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc = memory[rom[cpu->pc] | rom[cpu->pc + 1] << 8];
        return 1;
        break;

    }
    return 0;
  }
}
