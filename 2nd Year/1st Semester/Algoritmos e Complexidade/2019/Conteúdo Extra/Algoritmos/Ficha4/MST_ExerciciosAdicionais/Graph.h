#ifndef Graph_h
#define Graph_h

#include "Fringe.h"
#include "QueueBuffer.h"

#define MAX_V 6
#define WHITE 0
#define GREY  1
#define BLACK 2

typedef struct edge *Graph[MAX_V];
typedef Weight GraphM[MAX_V][MAX_V];

void NewGraph(Graph);
void AddEdge(Graph, int, Vertex dest, Weight);
void PrintGraph(Graph);
void ClearGraph(Graph);
int PrimMST(Graph, int p[], int w[]);
int DijkstraSP(Graph, int o, int p[], int w[]);
void TransitiveClosure(Graph, int c[MAX_V][MAX_V]);
void TransitiveClosureW(GraphM, int c[MAX_V][MAX_V]);
int Excentricity(Graph, int v);
int HowManyD(Graph, int v, Weight w);

int TraversalDF(Graph, int v, int f[]);
int Root(int f[MAX_V], int v);
int InTree(int f[MAX_V], int a, int b);
void JoinTree(int f[MAX_V], int a, int b);
int Cost(Graph, int f[MAX_V]);
int Height(int f[MAX_V]);

#endif
