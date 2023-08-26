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



struct cpu_t {
  uint8_t x;
  uint8_t y;
  uint8_t sp;
  uint16_t pc;
  uint8_t flags;
  uint8_t acc;
  status_t status;
  uint8_t current_instruction;
  std::string status_message;
  bool live_debug;
};

void cpu_print(struct cpu_t *cpu);

