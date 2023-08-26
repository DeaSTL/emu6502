#include <stdint.h>
#include "instructions.h"
#include "cpu.h"



namespace emuops {
  void misc_step(uint8_t* memory, uint8_t* rom, struct cpu_t* cpu, void (*tick)()){
    switch(rom[cpu->pc]) {
      case IN_INX: // Increment X
        tick();
        cpu->x++;
        break;
      case IN_INY: // Increment Y
        tick();
        cpu->y++;
        break;
      case IN_TXA: // Transfer X to accumulator
        tick();
        cpu->acc = cpu->x;
        break;
      // case IN_BRK:
      //   tick();
      //   cpu->status_message = "Break at" + std::to_string(cpu->pc);
      //   cpu->status = status_t::STOPPED;
    }
  }
}
