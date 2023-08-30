#include <stdint.h>
#include "opsteps.h"
#include "instructions.h"
#include "cpu.h"


namespace emuops {
  int memory_step(uint8_t*memory, uint8_t* rom, cpu_t* cpu) {

    switch (rom[cpu->pc]) {
      case IN_STA_ZPG: // Store accumulator in zero page
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc]] = cpu->acc;
        return 1;
        break;
      case IN_STA_ABS: // Store accumulator in absolute
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | rom[cpu->pc + 1] << 8] = cpu->acc;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_STA_ABS_X: // Store accumulator in absolute
        cpu->pc++;
        cpu_tick(cpu);
        memory[(rom[cpu->pc] | (rom[cpu->pc + 1] << 8)) + cpu->x] = cpu->acc;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_STA_ABS_Y: // Store accumulator in absolute
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->y] = cpu->acc;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_STA_ZPG_X: // Store accumulator in zero page
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] + cpu->x] = cpu->acc;
        return 1;
        break;
    }
    return 0;
  }
}
