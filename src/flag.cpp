#include <stdint.h>
#include "instructions.h"
#include "cpu.h"


namespace emuops {
  int flag_step(uint8_t *memory, uint8_t *rom, cpu_t *cpu){
    switch(rom[cpu->pc]) {
      case IN_SEC: // Set carry flag
        cpu_tick(cpu);
        cpu->flags |= 0x01;
        return 1;
        break;
      case IN_CLC: // Clear carry flag
        cpu_tick(cpu);
        cpu->flags &= 0xfe;
        return 1;
        break;
    }
    return 0;
  }
}
