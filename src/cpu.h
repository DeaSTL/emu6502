#pragma once
#include <stdint.h>
#include <unistd.h>
#include <string>



typedef enum  {
  RUNNING = 0x00,
  STOPPED = 0x01,
  PAUSED = 0x02,
  ERROR = 0x03,
} status_t;

typedef struct cpu {
  uint8_t x = 0x00;
  uint8_t y = 0x00;
  uint8_t sp = 0x00;
  uint16_t pc = 0x0000;
  uint8_t flags = 0x00;
  uint8_t acc = 0x00;
  status_t status;
  uint8_t current_instruction;
  std::string status_message;
  bool live_debug = true;
  uint16_t clock;
  uint32_t clock_speed;
  uint8_t* memory;
  uint8_t* rom;
} cpu_t;



void cpu_destory(cpu_t* cpu);
void cpu_print(cpu_t *cpu);
void cpu_tick(cpu_t *cpu);
void cpu_step(cpu_t *cpu);
void cpu_init(cpu_t* cpu);
