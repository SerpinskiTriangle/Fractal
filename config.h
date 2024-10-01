#define POINT_COUNT 4     //change to however many "point" structs are in modelPoints
#define RECURSION_COUNT 2 //levels of recursion

#include "structs.h"//nothing here
//do not touch the "done" field, new entries should have it set to NULL or 0
struct point modelPoints[POINT_COUNT] = {
    {50 ,50 ,0},
    {100,50 ,0},
    {100,100,0},
    {50 ,100,0}
};

int modelEdges[POINT_COUNT*2] = {0,1,1,2,2,3,3,0};
//each pair (eg [0],[1]  and   [4],[5]  represent a connection between the two points who's indices are stored in that element of the edge array)
//[0]=0 and [1]=1 mean "connect the first point in the "modelpoints" array to the second point in the "modelPoints" array"
//[1] and [2] have no association whatsoever

