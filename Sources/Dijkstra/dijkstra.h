#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"
using namespace std;

void Dijkstra(graph *G, int s, double *dist, int *parent, dlobj** fromedge);