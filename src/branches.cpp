#include "cpu.h"
#include <cstdint>
#include <stdint.h>
#include "instructions.h"
#include <stdio.h>


namespace emuops {
  void branch_step(uint8_t* memory, uint8_t* rom, struct cpu_t *cpu, void (*tick)()) {
    switch(rom[cpu->pc]){
    case IN_JSR: // Jump to subroutine
      tick();
      cpu->pc++;
      tick();
      memory[cpu->sp] = cpu->pc;
      tick();
      cpu->sp--;
      tick();
      cpu->pc = rom[cpu->pc];
      break;
    case IN_BCS: // Branch if carry set
      tick();
      cpu->pc++;
      if(cpu->flags & 0x01) {
        tick();
        cpu->pc += rom[cpu->pc];
      }
      break;
    case IN_JMP_ABS: // Jump to absolute
      cpu->status_message = "Jumping to absolute";
      tick();
      cpu->pc++;
      tick();
      cpu->pc = rom[cpu->pc] | (rom[cpu->pc + 1] << 8);
      tick();
      cpu->pc++;
      break;
    case IN_JMP_IND: // Jump to indirect
      cpu->status_message = "Jumping to indirect";
      tick();
      cpu->pc++;
      tick();
      cpu->pc = memory[cpu->pc] | (memory[cpu->pc + 1] << 8);
      tick();
      cpu->pc++;
      break;
    case IN_BNE: // Branch if not equal
      cpu->status_message = "Branching if not equal";
      tick();
      cpu->pc++;
      if(!(cpu->flags & 0x01)) {
        tick();
        cpu->pc += (int8_t)rom[cpu->pc];
        cpu_print(cpu);
      }
      break;
    case IN_BEQ: // Branch if equal
      cpu->status_message = "Branching if equal";
      tick();
      cpu->pc++;
      if(( cpu->flags & 0x1 ) == 0x1) {
        tick();
        cpu->pc += (int8_t)rom[cpu->pc];
        cpu_print(cpu);
      }
      break;
    case IN_BPL: // Branch if positive
      tick();
      cpu->pc++;
      if(!(cpu->flags & 0x80)) {
        tick();
        cpu->pc += rom[cpu->pc];
      }
      break;
    case IN_BMI: // Branch if negative
      tick();
      cpu->pc++;
      if(cpu->flags & 0x80) {
        tick();
        cpu->pc += rom[cpu->pc];
      }
      break;
    case IN_BVC: // Branch if overflow clear 
      tick();
      cpu->pc++;
      if(!(cpu->flags & 0x40)) {
        tick();
        cpu->pc += rom[cpu->pc];
      }
      break;
    }
  }
}
