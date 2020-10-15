#include <stdio.h>
#include "Graph.h"
#include "Kruskal.h"


int main(void)
{
	/*
	FringeV f = NewFringeV(10);
	int i = 0;

	f = AddFringeV(f, 5, 3);
	f = AddFringeV(f, 1, 4);
	f = AddFringeV(f, 2, 6);
	f = AddFringeV(f, 6, 8);
	f = AddFringeV(f, 4, 1);
	f = AddFringeV(f, 7, 5);
	f = AddFringeV(f, 9, 9);

	f = NextFringeV(f, &i);

	PrintFringeV(f);

	f = UpdateFringeV(f, 7, 0);

	PrintFringeV(f);
	ClearFringeV(f);
	*/
	
	/*
	FringeL f = NewFringeL(10);
	int i = 0;

	f = AddFringeL(f, 5, 3);
	f = AddFringeL(f, 1, 4);
	f = AddFringeL(f, 2, 6);
	f = AddFringeL(f, 6, 8);
	f = AddFringeL(f, 4, 1);
	f = AddFringeL(f, 7, 5);
	f = AddFringeL(f, 9, 9);

	f = NextFringeL(f, &i);

	PrintFringeL(f);

	f = UpdateFringeL(f, 7, 0);

	PrintFringeL(f);
	ClearFringeL(f);
	*/

	/*
	FringeH f = NewFringeH(10);
	int i = 0;

	f = AddFringeH(f, 5, 3);
	f = AddFringeH(f, 1, 4);
	f = AddFringeH(f, 2, 6);
	f = AddFringeH(f, 6, 8);
	f = AddFringeH(f, 4, 1);
	f = AddFringeH(f, 7, 5);
	f = AddFringeH(f, 9, 9);

	f = NextFringeH(f, &i);

	PrintFringeH(f);

	f = UpdateFringeH(f, 7, 0);

	PrintFringeH(f);
	ClearFringeH(f);
	*/

	/*
	Graph g;
	int p[MAX_V];
	int w[MAX_V];
	int i = 0;

	NewGraph(g);

	AddEdge(g, 0, 1, 4);
	AddEdge(g, 1, 3, 3);
	AddEdge(g, 1, 2, 10);
	AddEdge(g, 2, 1, 10);
	AddEdge(g, 2, 3, 7);
	AddEdge(g, 2, 4, 1);
	AddEdge(g, 3, 1, 3);
	AddEdge(g, 3, 2, 7);
	AddEdge(g, 3, 4, 2);
	AddEdge(g, 4, 2, 1);
	AddEdge(g, 4, 3, 2);

	PrintGraph(g);

	PrimMST(g, p, w);

	DijkstraSP(g, 0, p, w);

	for (i = 0; i < MAX_V; i++) {
		printf("%d - %d\n", i, p[i]);
	}

	printf("\n");

	ClearGraph(g);
	*/

	/*
	GraphK g = NewGraphK(4, 5);

	AddEdgeK(g, 0, 1, 10);
	AddEdgeK(g, 0, 2, 6);
	AddEdgeK(g, 0, 3, 5);
	AddEdgeK(g, 1, 3, 15);
	AddEdgeK(g, 2, 3, 4);

	//PrintGraphK(g);

	KruskalMST(g);

	ClearGraphK(g);
	*/

	/*
	Graph g;
	int c[MAX_V][MAX_V];
	int i = 0;
	int j = 0;

	NewGraph(g);

	AddEdge(g, 0, 1, 3);
	AddEdge(g, 0, 2, 5);
	AddEdge(g, 1, 2, 1);
	AddEdge(g, 2, 0, 9);
	AddEdge(g, 2, 3, 5);
	AddEdge(g, 3, 3, 8);

	TransitiveClosure(g, c);

	for (; i < MAX_V; i++) {
		for (j = 0; j < MAX_V; j++) {
			printf("%d ", c[i][j]);
		}

		printf("\n");
	}

	*/

	/*
	GraphM g = { 
		{ 1, 1, 0, 1 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 0, 0, 1 }
	};
	int c[MAX_V][MAX_V];
	int i = 0;
	int j = 0;

	TransitiveClosureW(g, c);

	for (; i < MAX_V; i++) {
		for (j = 0; j < MAX_V; j++) {
			printf("%d ", c[i][j]);
		}

		printf("\n");
	}

	*/

	/*
	Graph g;

	NewGraph(g);

	AddEdge(g, 0, 1, 4);
	AddEdge(g, 1, 0, 4);
	AddEdge(g, 1, 3, 3);
	AddEdge(g, 1, 2, 10);
	AddEdge(g, 2, 1, 10);
	AddEdge(g, 2, 3, 7);
	AddEdge(g, 2, 4, 1);
	AddEdge(g, 3, 1, 3);
	AddEdge(g, 3, 2, 7);
	AddEdge(g, 3, 4, 2);
	AddEdge(g, 4, 2, 1);
	AddEdge(g, 4, 3, 2);

	printf("Excentricity of Vertex 0: %d\n", Excentricity(g, 0));
	printf("HowMany D 10 from 0: %d\n", HowManyD(g, 0, 9));
	*/

	Graph g;
	int i = 0;
	int f[MAX_V];

	NewGraph(g);

	AddEdge(g, 0, 1, 1);
	AddEdge(g, 0, 2, 1);
	AddEdge(g, 1, 3, 1);
	AddEdge(g, 2, 5, 1);
	AddEdge(g, 3, 0, 1);
	AddEdge(g, 3, 4, 1);
	AddEdge(g, 4, 0, 1);
	AddEdge(g, 5, 0, 1);
	AddEdge(g, 5, 3, 1);
	AddEdge(g, 5, 4, 1);

	printf("Num reachable V from 0: %d\n", TraversalDF(g, 0, f));

	for (; i < MAX_V; i++) {
		printf("%d ", f[i]);
	}

	printf("\n");

	printf("Root of 4: %d\n", Root(f, 4));
	printf("1 and 4 Intree? %d\n", InTree(f, 1, 4));


	int gl[MAX_V] = { -1, 0, 1, 2, 5, -1 };

	printf("1 and 4 Intree? %d\n", InTree(gl, 1, 4));

	JoinTree(gl, 1, 4);

	printf("1 and 4 Intree? %d\n", InTree(gl, 1, 4));
	printf("Cost %d\n", Cost(g, f));
	printf("Height: %d\n", Height(f));

	ClearGraph(g);

	getchar();
	return 0;
}