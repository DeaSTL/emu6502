#include <stdint.h>
#include "instructions.h"
#include "cpu.h"
#include "opsteps.h"

namespace emuops {
  int math_step(uint8_t* memory, uint8_t* rom, cpu_t *cpu){
    cpu->current_instruction = rom[cpu->pc];
    switch(rom[cpu->pc]) {
      case IN_ADC_ZPG: // Add with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc += memory[rom[cpu->pc]];
        return 1;
        break;
      case IN_ADC_ZPG_X: // Add with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc += memory[rom[cpu->pc] + cpu->x];
        return 1;
        break;
      case IN_ADC_IMM: // Add with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc += rom[cpu->pc];
        return 1;
        break;
      case IN_ADC_ABS: // Add with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc += memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)];
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_ADC_ABS_X: // Add with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc += memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x];
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_SBC_ZPG: // Subtract with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc -= memory[rom[cpu->pc]];
        return 1;
        break;
      case IN_SBC_ZPG_X: // Subtract with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc -= memory[rom[cpu->pc] + cpu->x];
        return 1;
        break;
      case IN_SBC_IMM: // Subtract with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc -= rom[cpu->pc];
        return 1;
        break;
      case IN_SBC_ABS: // Subtract with carry
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc -= memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)];
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_SBC_ABS_X: // Subtract with carry 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc -= memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x];
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_INC_ZPG: // Increment memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc]]++;
        return 1;
        break;
      case IN_INC_ZPG_X: // Increment memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] + cpu->x]++;
        return 1;
        break;
      case IN_INC_ABS: // Increment memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]++;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_INC_ABS_X: // Increment memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x]++;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_DEC_ZPG: // Decrement memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc]]--;
        return 1;
        break;
      case IN_DEC_ZPG_X: // Decrement memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] + cpu->x]--;
        return 1;
        break;
      case IN_DEC_ABS: // Decrement memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)]--;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_DEC_ABS_X: // Decrement memory 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x]--;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_ROL_ACC: // Rotate left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc = cpu->acc << 1;
        return 1;
        break;
      case IN_ROL_ZPG: // Rotate left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc]] = memory[rom[cpu->pc]] << 1;
        return 1;
        break;
      case IN_ROL_ZPG_X: // Rotate left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] + cpu->x] = memory[rom[cpu->pc] + cpu->x] << 1;
        return 1;
        break;
      case IN_ROL_ABS: // Rotate left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] << 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_ROL_ABS_X: // Rotate left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] << 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_ROR_ACC: // Rotate right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc = cpu->acc >> 1;
        return 1;
        break;
      case IN_ROR_ZPG: // Rotate right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc]] = memory[rom[cpu->pc]] >> 1;
        return 1;
        break;
      case IN_ROR_ZPG_X: // Rotate right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] + cpu->x] = memory[rom[cpu->pc] + cpu->x] >> 1;
        return 1;
        break;
      case IN_ROR_ABS: // Rotate right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] >> 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_ROR_ABS_X: // Rotate right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] >> 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_ASL_ACC: // Arithmetic shift left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc = cpu->acc << 1;
        return 1;
        break;
      case IN_ASL_ZPG: // Arithmetic shift left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc]] = memory[rom[cpu->pc]] << 1;
        return 1;
        break;
      case IN_ASL_ZPG_X: // Arithmetic shift left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] + cpu->x] = memory[rom[cpu->pc] + cpu->x] << 1;
        return 1;
        break;
      case IN_ASL_ABS: // Arithmetic shift left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] << 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_ASL_ABS_X: // Arithmetic shift left 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] << 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_LSR_ACC: // Logical shift right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        cpu->acc = cpu->acc >> 1;
        return 1;
        break;
      case IN_LSR_ZPG: // Logical shift right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc]] = memory[rom[cpu->pc]] >> 1;
        return 1;
        break;
      case IN_LSR_ZPG_X: // Logical shift right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] + cpu->x] = memory[rom[cpu->pc] + cpu->x] >> 1;
        return 1;
        break;
      case IN_LSR_ABS: // Logical shift right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8)] >> 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
      case IN_LSR_ABS_X: // Logical shift right 
        cpu_tick(cpu);
        cpu->pc++;
        cpu_tick(cpu);
        memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] = memory[rom[cpu->pc] | (rom[cpu->pc + 1] << 8) + cpu->x] >> 1;
        cpu_tick(cpu);
        cpu->pc++;
        return 1;
        break;
    }
    return 0;
  }
}
