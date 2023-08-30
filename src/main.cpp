#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <unistd.h>
#include "cpu.h"
#include "opsteps.h"
#include "render.h"
#include <thread>
#include <chrono>


bool live_debug = true;
cpu_t *cpu;
std::thread render_thread;
std::thread event_thread;
void dumpMemoryToFile(uint8_t* memory, int size, std::string filename){
  FILE* file = fopen(filename.c_str(), "wb");
  fwrite(memory, 1, size, file);
  fclose(file);
}

int main(int argc, char *argv[])
{
  printf("Initializing CPU\n");
  cpu = (cpu_t*)malloc(sizeof(cpu_t));
  printf("Initializing CPU Memory\n");
  cpu_init(cpu);
  printf("Starting CPU\n");
  if(argc < 2) {
    printf("Usage: %s <rom>\n", argv[0]);
    printf("No rom specified, reverting to example rom\n");
  }
  std::string example_rom = std::string("../asm/test.o");
  FILE *rom_file = fopen(argv[1], "rb");
  printf("Opening rom file\n");
  if(!rom_file) {
    printf("Could not open rom file\n");
    return 1;
  }
  fread(cpu->rom, 1, 0xffff, rom_file);

  printf("Initializing Graphics\n");
  render::init(cpu);
  
  cpu->live_debug = live_debug;
  int batch_size = 10000;
  while (cpu->status == RUNNING){
    auto start = std::chrono::high_resolution_clock::now();
    render::eventLoop();
    for(int i = 0; i < batch_size; i++){
      cpu_tick(cpu);
      cpu_step(cpu);
    }
    auto end = std::chrono::high_resolution_clock::now();
    int delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    render::updatePallet();
    render::draw();
    if(cpu->live_debug){
      if(cpu->clock % 10000 == 1){
        printf("Acc: 0x%x\n", cpu->acc);
        printf("Program Counter: 0x%x\n", cpu->pc);
        printf("Flags: 0x%x\n", cpu->flags);
        printf("X: 0x%x\n", cpu->x);
        printf("Y: 0x%x\n", cpu->y);
        printf("Status: %d\n", cpu->status);
        printf("Flags: %b\n", cpu->flags);
        printf("SP: 0x%x\n", cpu->sp);
        printf("Delta: %d microseconds\n",delta);
        printf("Clock Cycles Per Second: %d\n",(float)(batch_size/delta) * 1000000);
        printf("Mhz %f\n", (float)((batch_size/delta) * 1000000)/ 1000000);
        //Clear line line below before printing
        printf("\033[2K");
        //printf("Status Message: %s\n", cpu->status_message.c_str());
        printf("Current Instruction: 0x%x\n", cpu->current_instruction);
        printf("Clock: %d\n", cpu->clock);
        // if(cpu->clock > 0xfff){
        //   dumpMemoryToFile(cpu->memory, 0xffff, "memory_dump.bin");
        //   printf("Dumped memory to memory_dump.bin\n");
        //   cpu->status = status_t::STOPPED;
        // }
        if(cpu->status == status_t::RUNNING) {
          for(int i = 0; i < 13; i++) {
            printf("\033[A");
          }
        }
      }
    }
    cpu_tick(cpu);
  }
  printf("Exited with status: %x\n", cpu->status);
  render::destroy();
  cpu_destory(cpu);
  free(rom_file);
  return 0;
}



