#include <stdint.h>
#include "opsteps.h"
#include "instructions.h"
#include "cpu.h"


namespace emuops {
  void memory_step(uint8_t*memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)()) {

    switch (rom[cpu->pc]) {
      case IN_STA_ZPG: // Store accumulator in zero page
        cpu->pc++;
        tick();
        memory[rom[cpu->pc]] = cpu->acc;
        break;
      case IN_STA_ABS: // Store accumulator in absolute
        cpu->pc++;
        tick();
        memory[rom[cpu->pc]] = cpu->acc;
        break;
      case IN_STA_ABS_X: // Store accumulator in absolute
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] = cpu->acc;
        tick();
        cpu->pc++;
        break;
      case IN_STA_ABS_Y: // Store accumulator in absolute
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->y] = cpu->acc;
        tick();
        cpu->pc++;
        break;
      case IN_STA_ZPG_X: // Store accumulator in zero page
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] + cpu->x] = cpu->acc;
        break;
    }
  }
}
