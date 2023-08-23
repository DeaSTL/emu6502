#include <stdint.h>
#include "instructions.h"
#include "cpu.h"
#include "opsteps.h"

namespace emuops {
  void math_step(uint8_t* memory, uint8_t* rom, struct cpu_t *cpu,void (*tick)()){
    cpu->current_instruction = rom[cpu->pc];
    switch(rom[cpu->pc]) {
      case IN_ADC_ZPG: // Add with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc += memory[rom[cpu->pc]];
        break;
      case IN_ADC_ZPG_X: // Add with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc += memory[rom[cpu->pc] + cpu->x];
        break;
      case IN_ADC_IMM: // Add with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc += rom[cpu->pc];
        break;
      case IN_ADC_ABS: // Add with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc += memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)];
        tick();
        cpu->pc++;
        break;
      case IN_ADC_ABS_X: // Add with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc += memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x];
        tick();
        cpu->pc++;
        break;
      case IN_SBC_ZPG: // Subtract with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc -= memory[rom[cpu->pc]];
        break;
      case IN_SBC_ZPG_X: // Subtract with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc -= memory[rom[cpu->pc] + cpu->x];
        break;
      case IN_SBC_IMM: // Subtract with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc -= rom[cpu->pc];
        break;
      case IN_SBC_ABS: // Subtract with carry
        tick();
        cpu->pc++;
        tick();
        cpu->acc -= memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)];
        tick();
        cpu->pc++;
        break;
      case IN_SBC_ABS_X: // Subtract with carry 
        tick();
        cpu->pc++;
        tick();
        cpu->acc -= memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x];
        tick();
        cpu->pc++;
        break;
      case IN_INC_ZPG: // Increment memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc]]++;
        break;
      case IN_INC_ZPG_X: // Increment memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] + cpu->x]++;
        break;
      case IN_INC_ABS: // Increment memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]++;
        tick();
        cpu->pc++;
        break;
      case IN_INC_ABS_X: // Increment memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x]++;
        tick();
        cpu->pc++;
        break;
      case IN_DEC_ZPG: // Decrement memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc]]--;
        break;
      case IN_DEC_ZPG_X: // Decrement memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] + cpu->x]--;
        break;
      case IN_DEC_ABS: // Decrement memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]--;
        tick();
        cpu->pc++;
        break;
      case IN_DEC_ABS_X: // Decrement memory 
        tick();
        cpu->pc++;
        tick();
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x]--;
        tick();
        cpu->pc++;
        break;
    }
  }
}
