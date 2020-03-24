#ifndef Graphs_h
#define Graphs_h

#define NE 0
#define MAX_SIZE 5
#define NIL -1

#define WHITE 0
#define GREY 1
#define BLACK 2

#define INTREE 0
#define FRINGE 1
#define UNSEEN 2

typedef int WEIGHT;

typedef WEIGHT GraphM[MAX_SIZE][MAX_SIZE];
typedef struct graphL *GraphL[MAX_SIZE];

void GraphMtoL(GraphM, GraphL, int size);
void GraphLtoM(GraphL, GraphM, int size);
int InDegreeL(GraphL, int v, int size);
int InDegreeM(GraphM, int v, int size);
int OutDegreeL(GraphL, int v);
int OutDegreeM(GraphM, int v, int size);
WEIGHT CapacityL(GraphL, int v, int size);
WEIGHT CapacityM(GraphM, int v, int size);
int MaxCapL(GraphL, int size);
int MaxCapM(GraphM, int size);
int ColorOKL(GraphL, int color[], int size);
int ColorOKM(GraphM, int color[], int size);
void InverseL(GraphL, GraphL inverse, int size);
void InverseM(GraphM, GraphM inverse, int size);
void ClearGraphL(GraphL, int size);
void PrintGraphM(GraphM, int size);
void PrintGraphL(GraphL, int size);

int TarjanTopL(GraphL, int size, int tsort[]);
int KahnTopL(GraphL, int size, int tsort[]);
int SuccN(GraphL, int v, int size, int N);
int Connection(GraphL, int v1, int v2, int size, WEIGHT section);
int Unreachable(GraphL, int o, int size);



#endif
