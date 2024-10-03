#ifndef CONFIG_H
#define CONFIG h
    #define POINT_COUNT 4     //change to however many "point" structs are in modelPoints
    #define RECURSION_COUNT 3 //levels of recursion

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
    };
    //do not touch the "done" field, new entries should have it set to NULL or 0
    struct point principleModelPoints[POINT_COUNT] = {
        {0 ,0 ,0},
        {0,50 ,0},
        {100,100,0},
        {50 ,0,0}
    };

    int principleModelEdges[POINT_COUNT*2] = {0,1,1,2,2,3,3,0};
    //each pair (eg [0],[1]  and   [4],[5]  represent a connection between the two points who's indices are stored in that element of the edge array)
    //[0]=0 and [1]=1 mean "connect the first point in the "modelpoints" array to the second point in the "modelPoints" array"
    //[1] and [2] have no association whatsoever

    
#endif

