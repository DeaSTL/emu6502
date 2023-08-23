#include <stdint.h>
#include "instructions.h"
#include "cpu.h"
#include "opsteps.h"
#include <stdio.h>

namespace emuops {
  void compare_step(uint8_t* memory, uint8_t* rom, struct cpu_t *cpu, void (*tick)()){
    switch(rom[cpu->pc]) {
      case IN_CMP_IMM: // Compare immediate
        tick();
        cpu->pc++;
        if(cpu->acc == rom[cpu->pc]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        printf("CMP_IMM: %d\n", rom[cpu->pc]);
        break;
      case IN_CMP_ZPG: // Compare zero page
        tick();
        cpu->pc++;
        if(cpu->acc == memory[rom[cpu->pc]]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        break;
      case IN_CMP_ZPG_X: // Compare zero page
        tick();
        cpu->pc++;
        if(cpu->acc == memory[rom[cpu->pc] + cpu->x]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        break;
      case IN_CMP_ABS: // Compare absolute
        tick();
        cpu->pc++;
        if(cpu->acc == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        tick();
        cpu->pc++;
        break;
      case IN_CMP_ABS_X: // Compare absolute 
        tick();
        cpu->pc++;
        if(cpu->acc == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        tick();
        cpu->pc++;
        break;
    }

  }
}
