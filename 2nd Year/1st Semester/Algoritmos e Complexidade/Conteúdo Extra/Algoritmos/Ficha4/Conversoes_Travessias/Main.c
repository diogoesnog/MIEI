#include <stdio.h>
#include "Graphs.h"


int main(void)
{
	int n = 9;
	int v = 4;
	GraphL gl;
	GraphL inverseL;
	GraphM inverseM;
	GraphM gm = {
		{ NE,  2, NE, NE, NE,  7,  3, NE, NE },
		{ 2, NE,  4, NE, NE, NE,  6, NE, NE },
		{ NE,  4, NE,  2, NE, NE, NE,  2, NE },
		{ NE, NE,  2, NE,  1, NE, NE,  8, NE },
		{ NE, NE, NE,  1, NE,  6, NE, NE,  2 },
		{ 7, NE, NE, NE,  6, NE, NE, NE,  5 },
		{ 3,  6, NE, NE, NE, NE, NE,  3,  1 },
		{ NE, NE,  2,  8, NE, NE,  3, NE,  4 },
		{ NE, NE, NE, NE,  2,  5,  1,  4, NE }
	};
	int color1[9] = { 3, 2, 1, 3, 1, 2, 1, 2, 3 };
	int color2[9] = { 1, 2, 1, 3, 1, 1, 3, 2, 3 };

	GraphMtoL(gm, gl, n);
	PrintGraphL(gl, n);

	printf("InDegreeL %d: %d\n", v, InDegreeL(gl, v, n));
	printf("InDegreeM %d: %d\n", v, InDegreeM(gm, v, n));

	printf("OutDegreeL %d: %d\n", v, OutDegreeL(gl, v));
	printf("OutDegreeM %d: %d\n", v, OutDegreeM(gm, v, n));

	printf("CapacityL %d: %d\n", v, CapacityL(gl, v, n));
	printf("CapacityM %d: %d\n", v, CapacityM(gm, v, n));

	printf("MaxCapacityL V: %d\n", MaxCapL(gl, n));
	printf("MaxCapacityM V: %d\n", MaxCapM(gm, n));

	printf("Color 1 L OK: %d\n", ColorOKL(gl, color1, n));
	printf("Color 2 L OK: %d\n", ColorOKL(gl, color2, n));
	printf("Color 1 M OK: %d\n", ColorOKM(gm, color1, n));
	printf("Color 2 M OK: %d\n", ColorOKM(gm, color2, n));

	printf("\n\nInverse:\n");
	InverseL(gl, inverseL, n);
	PrintGraphL(inverseL, n);

	InverseM(gm, inverseM, n);
	PrintGraphM(inverseM, n);

	ClearGraphL(gl, n);
	ClearGraphL(inverseL, n);

	/*int n = 5;
	int topsort[5];
	int i = 0;
	GraphM gm = {
		{ NE, NE, NE, NE,  1 },
		{ NE, NE, NE,  1, NE },
		{ NE,  1, NE, NE,  3 },
		{ NE, NE, NE, NE, NE },
		{ NE, NE, NE,  3, NE },
	};
	GraphL gl;

	GraphMtoL(gm, gl, n);

	TarjanTopL(gl, n, topsort);

	printf("TopSortL Tarjan: ");

	for (; i < n; i++) {
		printf("%d ", topsort[i]);
	}

	printf("\n\n");

	for (i = 0; i < n; i++) {
		topsort[i] = -1;
	}

	KahnTopL(gl, n, topsort);

	printf("TopSortL Kahn: ");

	for (i = 0; i < n; i++) {
		printf("%d ", topsort[i]);
	}

	printf("\n\n");

	printf("V 2 distance 1: %d\n", SuccN(gl, 0, n, 1));
	printf("V 2 distance 2: %d\n", SuccN(gl, 0, n, 2));

	printf("Connection from 2 to 3 with section superior to 2? %d\n",
		   Connection(gl, 2, 3, n, 2));

	printf("Unreachable v from 0: %d\n", Unreachable(gl, 0, n));
	printf("Unreachable v from 2: %d\n", Unreachable(gl, 2, n));

	ClearGraphL(gl, n);*/

	getchar();
	return 0;
}