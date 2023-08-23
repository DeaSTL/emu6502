#include "instructions.h"
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "cpu.h"
#include "opsteps.h"


uint16_t clock = 0;
uint32_t clock_speed = 500000;


void tick() {
  clock++;
  usleep(clock_speed);
}
struct cpu_t *cpu;
uint8_t memory[0xffff];
uint8_t rom[0xffff];



int step() {
  

  emuops::math_step(memory, rom, cpu, tick); 
  emuops::compare_step(memory, rom, cpu, tick);
  emuops::branch_step(memory, rom, cpu, tick);
  emuops::load_step(memory, rom, cpu, tick);
  emuops::flag_step(memory, rom, cpu, tick);
  emuops::misc_step(memory, rom, cpu, tick);
  emuops::memory_step(memory, rom, cpu, tick);

  tick();
  cpu->pc++;
  if(cpu->pc >= 0xffff) {
    printf("PC out of bounds\n");
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if(argc < 2) {
    printf("Usage: %s <rom>\n", argv[0]);
    return 1;
  }
  FILE *rom_file = fopen(argv[1], "rb");
  if(!rom_file) {
    printf("Could not open rom file\n");
    return 1;
  }
  fread(rom, 1, 0xffff, rom_file);
  cpu = (struct cpu_t *)malloc(sizeof(struct cpu_t));
  

  uint8_t state = RUNNING;
  while (state == RUNNING){
    printf("Acc: 0x%x\n", cpu->acc);
    printf("Program Counter: 0x%x\n", cpu->pc);
    printf("Flags: 0x%x\n", cpu->flags);
    printf("X: 0x%x\n", cpu->x);
    printf("Y: 0x%x\n", cpu->y);
    printf("Status: %d\n", cpu->status);
    printf("Clock: %d\n", clock);
    printf("Current Instruction: 0x%x\n", cpu->current_instruction);
    for(int i = 0; i < 32; i++) {
      printf("0x%x ", memory[i]);
      if(i % 8 == 7 && i != 0) {
        printf("\n");
      }
    }
    printf("\n");
    for(int i = 0; i < 13; i++) {
      printf("\033[A");
    }
    state = step();
  }
  printf("Exited with state: %x\n", state);
  return 0;
}



