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

struct model *makeModel(struct point points[POINT_COUNT], int edges[POINT_COUNT*2], unsigned int order){
    struct model *model =(struct model*)calloc(1, sizeof(struct model));
    for (int i = 0; i < POINT_COUNT; i++){
        model->points[i] = points[i];
        model->edges[i*2] = edges[i*2];
        model->edges[i*2 + 1] = edges[i*2 + 1];
    }
    model->done = 0;
    model->order = 0;
    return model;
};

struct model rotate180(struct model *model, unsigned int index){
    struct point normalizeVector = model->points[index];
    for (int i = 0; i < POINT_COUNT; i++){
        model->points[i].x -= normalizeVector.x;
        model->points[i].x *= -1;
        model->points[i].x += normalizeVector.x;

        model->points[i].y -= normalizeVector.y;
        model->points[i].y *= -1;
        model->points[i].y += normalizeVector.y;
    }
    return *model;
}

struct model scaleModel(struct model *model, double scale, unsigned int index){
    struct point normalizeVector = model->points[index];
    for (int i = 0; i < POINT_COUNT; i++){
        model->points[i].x -= normalizeVector.x;
        model->points[i].x *= scale;
        model->points[i].x += normalizeVector.x;

        model->points[i].y -= normalizeVector.y;
        model->points[i].y *= scale;
        model->points[i].y += normalizeVector.y;
    }
    return *model;
}

struct model shiftModel(struct model *model, double x, double y){
    for (int i = 0; i < POINT_COUNT; i++){
        model->points[i].x += x;
        model->points[i].y += y;
    }
    return *model;
}


void drawModel(struct model model){
    for (int i = 0; i < POINT_COUNT*2; i++){
        SDL_RenderDrawLine(renderer, 
        model.points[model.edges[i+0]].x, 
        model.points[model.edges[i+0]].y,
        model.points[model.edges[i+1]].x, 
        model.points[model.edges[i+1]].y);
    }
    for (int i = 0; i < POINT_COUNT; i++){
        SDL_RenderDrawPointF(renderer, model.points[i].x, model.points[i].y);
    }
    //printf("model drawn at %e,%e, 2%e, 2%e\r", model.points->x,model.points->y,model.points[1].x,model.points[1].y);
}


 
int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowHeight, windowWidth, 0,&window,&renderer);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    initModlelList();
    
    struct model *principleModel = makeModel(principleModelPoints, principleModelEdges, 0);
    globalModelList[0] = principleModel;
    scaleModel(globalModelList[0], globalScale, 0);
    shiftModel(globalModelList[0], globalShiftX, globalShiftY);
    modelCount++;

    for (unsigned int recursionLevel = 0; recursionLevel <= RECURSION_COUNT; recursionLevel++){
        unsigned int pendingModelCount = 0;

        for (unsigned int currentWorkingModelIndex = 0; currentWorkingModelIndex < modelCount; currentWorkingModelIndex++){
            if (globalModelList[currentWorkingModelIndex]->done){
                continue;
            }

            for (unsigned int currentWorkingPointIndex = 0; currentWorkingPointIndex < POINT_COUNT; currentWorkingPointIndex++){
                if (globalModelList[currentWorkingModelIndex]->points[currentWorkingPointIndex].done){
                    continue;
                }

                struct model *newModel = makeModel(principleModelPoints, principleModelEdges, recursionLevel);

                if (recursionLevel % 2 == 0){
                    rotate180(newModel, currentWorkingPointIndex);
                }

                scaleModel(newModel, (1/pow(2, recursionLevel+1))*globalScale, currentWorkingPointIndex);//change scale function here

                shiftModel(newModel, 
                globalModelList[currentWorkingModelIndex]->points[currentWorkingPointIndex].x - newModel->points[currentWorkingPointIndex].x, 
                globalModelList[currentWorkingModelIndex]->points[currentWorkingPointIndex].y - newModel->points[currentWorkingPointIndex].y);

                newModel->points[currentWorkingPointIndex].done = 1;

                globalModelList[modelCount + pendingModelCount] = newModel;

                pendingModelCount++;

                globalModelList[currentWorkingModelIndex]->points[currentWorkingPointIndex].done = 1;
            }
        }
        modelCount += pendingModelCount;
    }


    while (running) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
                break;
            }
        }
        

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);


        for (int i = 0; i < modelCount; i++){
            srand(i + 5);
            double o = fabs(rand()/(double)RAND_MAX);
            SDL_SetRenderDrawColor(renderer, (int)(255 - i* 20),(int)(255 * 0),(int)(255 + i*20),255);
            drawModel(*(globalModelList[i]));
        }
        

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    printf("\n");
    printf("model drawn at %e,%e, 2%e, 2%e\r",globalModelList[0]->points->x,globalModelList[0]->points->y,globalModelList[0]->points[2].x,globalModelList[0]->points[2].y);
    printf("\nmodels:%d", modelCount);

    for (int i = 0; i < modelCount; i++){
        free(globalModelList[i]);
    }
    free(globalModelList);

    printf("\n");

    return 0;
}
