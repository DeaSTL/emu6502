#include "cpu.h"
#include "opsteps.h"






void cpu_init(cpu_t* cpu) {
  cpu->x = 0x00;
  printf("Initializing x register\n");
  cpu->y = 0x00;
  printf("Initializing y register\n");
  cpu->sp = 0xff;
  printf("Initializing sp register\n");
  cpu->pc = 0x0000;
  printf("Initializing pc register\n");
  cpu->flags = 0x00;
  printf("Initializing flags register\n");
  cpu->acc = 0x00;
  printf("Initializing acc register\n");
  cpu->status = status_t::RUNNING;
  printf("Initializing status register\n");
  cpu->current_instruction = 0x00;
  printf("Initializing current_instruction register\n");
  cpu->live_debug = true;
  printf("Initializing live_debug register\n");
  cpu->clock = 0;
  printf("Initializing clock register\n");
  cpu->clock_speed = 50000;
  printf("Initializing clock_speed register\n");
  cpu->memory = (uint8_t*)malloc(0xffff);
  printf("Initializing memory\n");
  cpu->rom = (uint8_t*)malloc(0xffff);
  printf("Initializing rom\n");
}


void cpu_tick(cpu_t *cpu) {
  cpu->clock++;
  // usleep(1);
}




void cpu_print(cpu_t *cpu){
  if(cpu->live_debug) return;
  // printf("CPU:\n");
  // printf("  X: 0x%x\n", cpu->x);
  // printf("  Y: 0x%x\n", cpu->y);
  // printf("  SP: 0x%x\n", cpu->sp);
  // printf("  PC: 0x%x\n", cpu->pc);
  // printf("  Flags: 0x%b\n", cpu->flags);
  // printf("  Acc: 0x%x\n", cpu->acc);
  // printf("  Status: 0x%x\n", cpu->status);
  // printf("  Current Instruction: 0x%x\n", cpu->current_instruction);
  // printf("  Status Message: %s\n", cpu->status_message.c_str());
}
void cpu_continue(cpu_t *cpu){
  cpu->pc++;
  if(cpu->pc >= 0xffff) {
    printf("PC out of bounds\n");
    cpu->status = status_t::STOPPED;
  }
}
void cpu_step(cpu_t *cpu){
  if(emuops::memory_step(cpu->memory, cpu->rom, cpu)){ cpu_continue(cpu); return; }
  if(emuops::math_step(cpu->memory, cpu->rom, cpu)){ cpu_continue(cpu); return; }
  if(emuops::compare_step(cpu->memory, cpu->rom, cpu)){ cpu_continue(cpu); return; }
  if(emuops::branch_step(cpu->memory, cpu->rom, cpu)){ cpu_continue(cpu); return; }
  if(emuops::load_step(cpu->memory, cpu->rom, cpu)){ cpu_continue(cpu); return; }
  if(emuops::flag_step(cpu->memory, cpu->rom, cpu)){ cpu_continue(cpu); return; }
  if(emuops::misc_step(cpu->memory, cpu->rom, cpu)){ cpu_continue(cpu); return; }


}

void cpu_destory(cpu_t* cpu) {
  free(cpu->memory);
  free(cpu->rom);
  free(cpu);
}


