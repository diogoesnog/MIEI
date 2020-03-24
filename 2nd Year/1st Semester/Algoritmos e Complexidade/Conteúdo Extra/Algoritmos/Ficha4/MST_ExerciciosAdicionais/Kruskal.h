#ifndef Kruskal_h 
#define Kruskal_h

typedef int Vertex;
typedef int Weight;

typedef struct graphK *GraphK;


GraphK NewGraphK(int V, int E);
void AddEdgeK(GraphK, Vertex source, Vertex dest, Weight);
void PrintGraphK(GraphK);
void ClearGraphK(GraphK);
void KruskalMST(GraphK);

#endif 

