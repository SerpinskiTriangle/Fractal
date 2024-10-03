#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include "../include/SDL.h"
#include "config.h"
#include "structs.h"
#include <stdlib.h>


void initModlelList(){
    int addedModels = 0;
    for (int i = 0; i <RECURSION_COUNT; i++){
        addedModels += (int)pow(POINT_COUNT-1,i);
    }

    int maxModels = 1 +//base model, given at RECURSION_COUNT = 0
        addedModels * POINT_COUNT; //all successive models have 1 point (braching point) that should not be retraced
        
    printf("%d models to be rendered\n", maxModels);
    //most epic calloc call ever?!1??!1!!
    //segfault count:
    globalModelList = (struct model **)calloc(maxModels, sizeof(struct model));
}

struct model *makeModel(struct point points[POINT_COUNT], int edges[POINT_COUNT*2]){
    struct model *model =(struct model*)calloc(1, sizeof(struct model));
    for (int i = 0; i < POINT_COUNT; i++){
        model->points[i] = points[i];
        model->edges[i*2] = edges[i*2];
        model->edges[i*2 + 1] = edges[i*2 + 1];
    }
    model->done = 0;
    return model;
};

struct model shiftRotateScale(struct model model, unsigned int index, double scale){
    struct point normalizeVector = model.points[index];
    for (int i = 0; i < POINT_COUNT; i++){
        model.points[i].x -= normalizeVector.x;
        model.points[i].x *= -scale;
        model.points[i].x += normalizeVector.x;

        model.points[i].y -= normalizeVector.y;
        model.points[i].y *= -scale;
        model.points[i].y += normalizeVector.y;
    }
    return model;
}

struct model shiftModel(struct model model, double x, double y){
    for (int i = 0; i < POINT_COUNT; i++){
        model.points[i].x += x;
        model.points[i].y += y;
    }
    return model;
}




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
    printf("model drawn at %e,%e, 2%e, 2%e\r", model.points->x,model.points->y,model.points[1].x,model.points[1].y);
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(600, 600, 0,&window,&renderer);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    initModlelList();
    
    struct model *principleModel = makeModel(principleModelPoints, principleModelEdges);
    globalModelList[0] = principleModel;
    modelCount++;


    while (running) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
                break;
            }
        }
        

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        drawModel(**globalModelList);
        drawModel(shiftModel(**globalModelList,50,50));

        for (int i = 0; i < modelCount; i++){
            drawModel(*(globalModelList[i]));
        }
        

        SDL_RenderPresent(renderer);

    }

    printf("\n");
    printf("model drawn at %e,%e, 2%e, 2%e\r",globalModelList[0]->points->x,globalModelList[0]->points->y,globalModelList[0]->points[2].x,globalModelList[0]->points[2].y);

    printf("/nmodels:%d", modelCount);
    for (int i = 0; i < modelCount; i++){
        free(globalModelList[i]);
    }

    free(globalModelList);

    printf("\n");

    return 0;
}
