#include <stdint.h>
#include "instructions.h"
#include "cpu.h"



namespace emuops {
  int misc_step(uint8_t* memory, uint8_t* rom, cpu_t* cpu){
    switch(rom[cpu->pc]) {
      case IN_INX: // Increment X
        cpu_tick(cpu);
        cpu->x++;
        return 1;
        break;
      case IN_INY: // Increment Y
        cpu_tick(cpu);
        cpu->y++;
        return 1;
        break;
      case IN_TXA: // Transfer X to accumulator
        cpu_tick(cpu);
        cpu->acc = cpu->x;
        return 1;
        break;
      case IN_TYA:
        cpu_tick(cpu);
        cpu->acc = cpu->y;
        return 1;
        break;
      case IN_TAY:
        cpu_tick(cpu);
        cpu->y = cpu->acc;
        return 1;
        break;
      // case IN_BRK:
      //   cpu_tick(cpu);
      //   cpu->status_message = "Break at" + std::to_string(cpu->pc);
      //   cpu->status = status_t::STOPPED;
    }
    return 0;
  }
}
