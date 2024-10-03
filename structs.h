#ifndef STRUCTS_H
#define STRUCTS_H
    #include "../include/SDL.h"

    struct model **globalModelList; 
    unsigned int modelCount = 0;


    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    const Uint8 *keyboardState;
    SDL_Event event;

    char running = 1;
#endif