#include <stdint.h>
#include "instructions.h"
#include "cpu.h"

namespace emuops {
  void increment_step(uint8_t *memory[], uint8_t *rom[], struct cpu_t *cpu, void (*tick)()){
    switch(*rom[cpu->pc]) {
      case IN_NOP: // No operation
        tick();
        break;
      case IN_BRK: // Break
        tick();
        cpu->status = status_t::STOPPED;
      case IN_TAY: // Transfer accumulator to Y
        tick();
        cpu->y = cpu->acc;
        break;
    }
    
  }
}
