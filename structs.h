#ifndef STRUCTS_H
#define STRUCTS_H
    #include "../include/SDL.h"

    struct point{
        double x;
        double y;
        char done;//do not touch done
    };

    struct model{
        struct point *points;
        int *edges; //an array of point indices, each consecutive pair an edge
        int done;
    };

    struct model *models; 
    unsigned int modelCount = 0;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    const Uint8 *keyboardState;
    SDL_Event event;

    char running = 1;
#endif