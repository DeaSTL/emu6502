#include "render.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "cpu.h"
#include <unistd.h>

namespace render{
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  SDL_Event event;
  cpu_t* cpu;



  uint16_t pixel_width = 0x40;
  uint16_t pixel_height = 0x40;
  uint16_t pixel_total = pixel_width * pixel_height;
  uint16_t pixel_start = 0x1000;
  uint16_t palette_width = 0x10;
  uint16_t palette_start = pixel_start + (pixel_total / 2);


  Uint8 *palette;
  Uint8 *pixels;
  int pitch;
  uint8_t* getPaletteColor(uint8_t index){
    if(index > palette_width){
      printf("Palette index out of bounds: 0x%x\n", index);
      return &palette[0];
    }
    return &palette[index * 3];
  }
  void setPaletteColor(uint8_t index ,uint8_t r, uint8_t g, uint8_t b){
    if(index > palette_width){
      printf("Palette index out of bounds: 0x%x\n", index);
      return;
    }
    palette[index * 3] = r;
    palette[(index * 3) + 1] = g;
    palette[(index * 3) + 2] = b;
  }
  void setPixelWithIndex(uint16_t index, uint8_t color){
    uint8_t* pixel = &pixels[index * 3];
    uint8_t* color_rgb = getPaletteColor(color);
    pixel[0] = color_rgb[0];
    pixel[1] = color_rgb[1];
    pixel[2] = color_rgb[2];
  }
  void printArray(uint8_t* array, int size){
    for(int i = 0; i < size; i++){
      printf("0x%x ", array[i]);
    }
    printf("\n\n");
  }

  void eventLoop(){
    SDL_Event* event = &render::event;
    while(SDL_PollEvent(event)){

      if(event->type == SDL_QUIT){
        cpu->status = status_t::STOPPED;
      }

    }
  }
  int init(cpu_t* _cpu){
    palette = (Uint8* )malloc(palette_width * 3);
    pixels = (Uint8* )malloc(pixel_width * pixel_height * 3);
    cpu = _cpu;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Toy Console", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pixel_width, pixel_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, pixel_width, pixel_height);
    return 0;
  }
  void updatePallet(){
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    for(uint16_t  i = 0; i < palette_width; i++){
      r = cpu->memory[palette_start + (i*3)];
      g = cpu->memory[palette_start + (i*3) + 1];
      b = cpu->memory[palette_start + (i*3) + 2];
      setPaletteColor(i, r, g, b);
    }
  } 
  void draw(){
    // printArray(palette, palette_width * 3);
    uint8_t index_byte = 0;
    uint8_t index_l = 0;
    uint8_t index_h = 0;
    uint8_t* l_color;
    for(uint16_t i = 0; i < (pixel_width * pixel_height) / 2; i++){
      index_byte = cpu->memory[pixel_start + i];
      index_l = index_byte & 0x0f;
      index_h = (index_byte & 0xf0) >> 4;
      l_color = getPaletteColor(index_l);
      setPixelWithIndex((i), index_l);

      l_color = getPaletteColor(index_h);

      setPixelWithIndex((i)+1, index_h);
    }
    SDL_UpdateTexture(texture, NULL, pixels, pixel_width * 3);


    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
  void destroy(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free(palette);
    free(pixels);
    SDL_Quit();
  }

}
