#ifndef FringeMinHeap_h 
#define FringeMinHeap_h

#define PARENT(i) (i - 1) / 2
#define LEFT(i)   2 * i + 1
#define RIGHT(i)  2 * i + 2

typedef int Weight;
typedef int Vertex;

typedef struct fringe *Fringe;

Fringe NewFringe(int size);
Fringe AddV(Fringe, Vertex, Weight);
Fringe UpdateV(Fringe, Vertex, Weight);
Fringe NextV(Fringe, Vertex *);
void ClearFringe(Fringe);

#endif  

