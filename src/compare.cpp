#include <stdint.h>
#include "instructions.h"
#include "cpu.h"
#include "opsteps.h"
#include <stdio.h>
#include <string>

namespace emuops {
  void compare_step(uint8_t* memory, uint8_t* rom, struct cpu_t *cpu, void (*tick)()){
    switch(rom[cpu->pc]) {
      case IN_CMP_IMM: // Compare immediate
        cpu->status_message = "CMP_IMM";
        tick();
        cpu->pc++;
        if(cpu->acc == rom[cpu->pc]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
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
        cpu->status_message = "CMP_ZPG_X";
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
      case IN_CPX_IMM: // Compare X register immediate
        tick();
        cpu->pc++;
        if(cpu->x == rom[cpu->pc]) {
          tick();
          cpu->flags |= 0x01; // Set carry flag
        } else {
          tick();
          cpu->flags &= 0xfe; // Clear carry flag
        }
        break;
      case IN_CPX_ZPG: // Compare X register zero page 
        tick();
        cpu->pc++;
        if(cpu->x == memory[rom[cpu->pc]]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        break;
      case IN_CPX_ABS: // Compare X register absolute 
        tick();
        cpu->pc++;
        if(cpu->x == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        tick();
        cpu->pc++;
        break;
      case IN_CPY_IMM: // Compare Y register immediate 
        tick();
        cpu->pc++;
        if(cpu->y == rom[cpu->pc]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        break;
      case IN_CPY_ZPG: // Compare Y register zero page 
        tick();
        cpu->pc++;
        if(cpu->y == memory[rom[cpu->pc]]) {
          tick();
          cpu->flags |= 0x01;
        } else {
          tick();
          cpu->flags &= 0xfe;
        }
        break;
      case IN_CPY_ABS: // Compare Y register absolute 
        tick();
        cpu->pc++;
        if(cpu->y == memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]) {
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
