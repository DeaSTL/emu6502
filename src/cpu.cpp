#include "cpu.h"


void cpu_print(struct cpu_t *cpu){
  if(cpu->live_debug) return;
  printf("CPU:\n");
  printf("  X: 0x%x\n", cpu->x);
  printf("  Y: 0x%x\n", cpu->y);
  printf("  SP: 0x%x\n", cpu->sp);
  printf("  PC: 0x%x\n", cpu->pc);
  printf("  Flags: 0x%b\n", cpu->flags);
  printf("  Acc: 0x%x\n", cpu->acc);
  printf("  Status: 0x%x\n", cpu->status);
  printf("  Current Instruction: 0x%x\n", cpu->current_instruction);
  printf("  Status Message: %s\n", cpu->status_message.c_str());
}
