#include <stdint.h>
#include "instructions.h"
#include "cpu.h"
#include "opsteps.h"
#include <stdio.h>
#include <string>

namespace emuops {
  int compare_step(uint8_t* memory, uint8_t* rom, cpu_t *cpu){
    switch(rom[cpu->pc]) {
      case IN_CMP_IMM: // Compare immediate
        cpu_tick(cpu);
        cpu->pc++;
        if(cpu->acc == rom[cpu->pc]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        return 1;
        break;
      case IN_CMP_ZPG: // Compare zero page
        cpu_tick(cpu);
        cpu->pc++;
        if(cpu->acc == memory[rom[cpu->pc]]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        return 1;
        break;
      case IN_CMP_ZPG_X: // Compare zero page
        cpu_tick(cpu);
        cpu->pc++;
        if(cpu->acc == memory[rom[cpu->pc] + cpu->x]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        return 1;
        break;
      case IN_CMP_ABS: // Compare absolute
        cpu_tick(cpu);
        cpu->pc++;
        if(cpu->acc == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_CMP_ABS_X: // Compare absolute 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_print(cpu);
        if(cpu->acc == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_CPX_IMM: // Compare X register immediate
        cpu_tick(cpu);
        cpu->pc++;
        cpu_print(cpu);
        if(cpu->x == rom[cpu->pc]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01; // Set carry flag
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe; // Clear carry flag
        }
        return 1;
        break;
      case IN_CPX_ZPG: // Compare X register zero page 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_print(cpu);
        if(cpu->x == memory[rom[cpu->pc]]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        return 1;
        break;
      case IN_CPX_ABS: // Compare X register absolute 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_print(cpu);
        if(cpu->x == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_CPY_IMM: // Compare Y register immediate 
        cpu_tick(cpu);
        cpu->pc++;
        if(cpu->y == rom[cpu->pc]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        return 1;
        break;
      case IN_CPY_ZPG: // Compare Y register zero page 
        cpu_tick(cpu);
        cpu->pc++;
        if(cpu->y == memory[rom[cpu->pc]]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        return 1;
        break;
      case IN_CPY_ABS: // Compare Y register absolute 
        cpu_tick(cpu);
        cpu->pc++;
        if(cpu->y == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]) {
          cpu_tick(cpu);
          cpu->flags |= 0x01;
        } else {
          cpu_tick(cpu);
          cpu->flags &= 0xfe;
        }
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
    }
    return 0;

  }
}
