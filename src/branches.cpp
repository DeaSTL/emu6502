#include "cpu.h"
#include <cstdint>
#include <stdint.h>
#include "instructions.h"
#include <stdio.h>


namespace emuops {
  int branch_step(uint8_t* memory, uint8_t* rom, cpu_t *cpu) {
    switch(rom[cpu->pc]){
    case IN_JSR: // Jump to subroutine
      cpu_tick(cpu);
      cpu->pc++;
      cpu_tick(cpu);
      memory[cpu->sp] = cpu->pc;
      cpu_tick(cpu);
      cpu->sp--;
      cpu_tick(cpu);
      cpu->pc = rom[cpu->pc];
      return 1;
      break;
    case IN_BCS: // Branch if carry set
      cpu_tick(cpu);
      cpu->pc++;
      if(cpu->flags & 0x01) {
        cpu_tick(cpu);
        cpu->pc += rom[cpu->pc];
      }
      return 1;
      break;
    case IN_JMP_ABS: // Jump to absolute
      cpu_tick(cpu);
      cpu->pc++;
      cpu_tick(cpu);
      cpu->pc = rom[cpu->pc] | (rom[cpu->pc + 1] << 8);
      cpu_tick(cpu);
      return 1;
      break;
    case IN_JMP_IND: // Jump to indirect
      cpu_tick(cpu);
      cpu->pc++;
      cpu_tick(cpu);
      cpu->pc = memory[cpu->pc] | (memory[cpu->pc + 1] << 8);
      cpu_tick(cpu);
      return 1;
      break;
    case IN_BNE: // Branch if not equal
      cpu_tick(cpu);
      cpu->pc++;
      if(!(cpu->flags & 0x01)) {
        cpu_tick(cpu);
        cpu->pc += (int8_t)rom[cpu->pc];
        cpu_print(cpu);
      }
      return 1;
      break;
    case IN_BEQ: // Branch if equal
      cpu_tick(cpu);
      cpu->pc++;
      if(( cpu->flags & 0x1 ) == 0x1) {
        cpu_tick(cpu);
        cpu->pc += (int8_t)rom[cpu->pc];
        cpu_print(cpu);
      }
      return 1;
      break;
    case IN_BPL: // Branch if positive
      cpu_tick(cpu);
      cpu->pc++;
      if(!(cpu->flags & 0x80)) {
        cpu_tick(cpu);
        cpu->pc += rom[cpu->pc];
      }
      return 1;
      break;
    case IN_BMI: // Branch if negative
      cpu_tick(cpu);
      cpu->pc++;
      if(cpu->flags & 0x80) {
        cpu_tick(cpu);
        cpu->pc += rom[cpu->pc];
      }
      return 1;
      break;
    case IN_BVC: // Branch if overflow clear 
      cpu_tick(cpu);
      cpu->pc++;
      if(!(cpu->flags & 0x40)) {
        cpu_tick(cpu);
        cpu->pc += rom[cpu->pc];
      }
      return 1;
      break;
    }
    return 0;
  }
}
