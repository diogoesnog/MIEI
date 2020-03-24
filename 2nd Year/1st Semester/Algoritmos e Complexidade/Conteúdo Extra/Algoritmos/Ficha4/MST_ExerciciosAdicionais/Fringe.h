#ifndef Fringe_h
#define Fringe_h

typedef int Vertex;
typedef int Weight;


// Fringe Vector

typedef struct fringeVector *FringeV;

FringeV NewFringeV(int size);
FringeV NextFringeV(FringeV, Vertex *);
FringeV AddFringeV(FringeV, Vertex, Weight);
FringeV UpdateFringeV(FringeV, Vertex, Weight);
void PrintFringeV(FringeV);
void ClearFringeV(FringeV);


// Fringe List

typedef struct fringeList *FringeL;

FringeL NewFringeL(int size);
FringeL NextFringeL(FringeL, Vertex *);
FringeL AddFringeL(FringeL, Vertex, Weight);
FringeL UpdateFringeL(FringeL, Vertex, Weight);
void PrintFringeL(FringeL);
void ClearFringeL(FringeL);


// Fringe Heap

#define PARENT(i) (i - 1) / 2
#define LEFT(i)   2 * i + 1
#define RIGHT(i)  2 * i + 2

typedef struct fringeHeap *FringeH;

FringeH NewFringeH(int size);
FringeH NextFringeH(FringeH, Vertex *);
FringeH AddFringeH(FringeH, Vertex, Weight);
FringeH UpdateFringeH(FringeH, Vertex, Weight);
void PrintFringeH(FringeH);
void ClearFringeH(FringeH);

#endif
