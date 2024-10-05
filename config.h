#ifndef CONFIG_H
#define CONFIG h
    #define POINT_COUNT 8     //change to however many "point" structs are in modelPoints
    #define RECURSION_COUNT 6 //levels of recursion

    #include "structs.h"
    struct point{
        double x;
        double y;
        char done;//do not touch done
    };

    struct model{
        struct point points[POINT_COUNT];
        int edges[POINT_COUNT*2]; //an array of point indices, each consecutive pair an edge
        int done;
        unsigned int order;
    };
    
    double globalScale = 6;

    const unsigned int windowHeight = 800;
    const unsigned int windowWidth =  800;

    int globalShiftX = windowHeight/2 -100;//can be manually set if you so wish
    int globalShiftY = windowWidth/2  +80;

    //use done to exclude vertices from recusing
    struct point principleModelPoints[POINT_COUNT] = {
        {-20,20,0},
        {0,5,1},
        {20,20},
        {5,0,1},
        {20,-20,0},
        {0,-5,1},
        {-20,-20,0},
        {-5,0,1}

    };

    int principleModelEdges[POINT_COUNT*2] = {0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,0};
    //each pair (eg [0],[1]  and   [4],[5]  represent a connection between the two points who's indices are stored in that element of the edge array)
    //[0]=0 and [1]=1 mean "connect the first point in the "modelpoints" array to the second point in the "modelPoints" array"
    //[1] and [2] have no association whatsoever

    
    
#endif

