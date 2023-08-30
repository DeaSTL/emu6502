#include <stdint.h>
#include "instructions.h"
#include "cpu.h"

namespace emuops {
  int increment_step(uint8_t *memory[], uint8_t *rom[], cpu_t *cpu){
    switch(*rom[cpu->pc]) {
      case IN_NOP: // No operation
        cpu_tick(cpu);
        return 1;
        break;
      case IN_BRK: // Break
        cpu_tick(cpu);
        cpu->status = status_t::STOPPED;
        return 1;
        break;
      case IN_TAY: // Transfer accumulator to Y
        cpu_tick(cpu);
        cpu->y = cpu->acc;
        return 1;
        break;
    }
    return 0;
    
  }
}
