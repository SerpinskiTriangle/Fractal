#include <stdio.h>
#include <sys/types.h>
#include "../include/SDL.h"
#include "config.h"
#include <stdlib.h>

//1 + POINT_COUNT * (int)pow(POINT_COUNT-1, RECUTSION_COUNT)

void initModlelList(){
    int addedModels = 0;
    if (RECURSION_COUNT > 0){
        for (int i = 0; i <RECURSION_COUNT; i++){
            addedModels += (int)pow(POINT_COUNT-1,i);
        }
    }

    int maxModels = 1 +//base model, given at RECURSION_COUNT = 0
        addedModels * POINT_COUNT; //all successive models have 1 point (braching point) that should not be retraced
        
    printf("%d models to be rendered\n", maxModels);
    //most epic calloc call ever?!1??!1!!
    //segfault count:
    models = (struct model *)calloc(maxModels, sizeof(struct model));
}

struct model *makeModel(struct point points[POINT_COUNT], int edges[POINT_COUNT*2]){
    struct model *model =(struct model*)calloc(1, sizeof(struct model));
    model->points = points;
    model->edges = edges;
};


void drawModel(struct model model){
    SDL_SetRenderDrawColor(renderer, 50,50,50,0);
    for (int i = 0; i < POINT_COUNT*2; i++){
        SDL_RenderDrawLine(renderer, 
        model.points[model.edges[i+0]].x, 
        model.points[model.edges[i+0]].y,
        model.points[model.edges[i+1]].x, 
        model.points[model.edges[i+1]].y);
    }
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    for (int i = 0; i < POINT_COUNT; i++){
        SDL_RenderDrawPointF(renderer, model.points[i].x, model.points[i].y);
    }
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(600, 600, 0,&window,&renderer);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    initModlelList();
    
    struct model *model1 = makeModel(modelPoints, modelEdges);

    while (running) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        drawModel(*model1);


        SDL_RenderPresent(renderer);

        

    }
    free(models);
    return 0;
}
