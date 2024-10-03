#ifndef STRUCTS_H
#define STRUCTS_H
    #include "include/SDL.h"

    struct model **globalModelList; 
    unsigned int modelCount = 0;

    char rCol = 255;
    char gCol = 255;
    char bCol = 255;


    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    const Uint8 *keyboardState;
    SDL_Event event;

    char running = 1;
#endif