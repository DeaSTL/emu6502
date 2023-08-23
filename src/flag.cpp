#include <stdint.h>
#include "instructions.h"
#include "cpu.h"


namespace emuops {
  void flag_step(uint8_t *memory, uint8_t *rom, struct cpu_t *cpu, void (*tick)()){
    switch(rom[cpu->pc]) {
      case IN_SEC: // Set carry flag
        tick();
        cpu->flags |= 0x01;
        break;
      case IN_CLC: // Clear carry flag
        tick();
        cpu->flags &= 0xfe;
        break;
    }
  }
}
