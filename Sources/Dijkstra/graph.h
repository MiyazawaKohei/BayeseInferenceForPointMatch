#include <stdio.h>
#ifndef GRAPH_T
#define GRAPH_T

typedef struct dlobj {
    struct dlobj *next;
    struct dlobj *prev;
    int v;
    double w;
} dlobj;

typedef struct {
    dlobj *nil;
} dlist;


typedef struct {
  int n; // �ߓ_��
  int m; // �}��
  dlist **E; // �}���X�g�̔z��
} graph;


graph *graph_input();
graph *graph_input_undirected(FILE *in);
void graph_free(graph *G); // �O���t���J������
void graph_print(graph *G); // �O���t�̒��g��\������
dlobj *graph_firstedge(graph *G, int i);
dlobj *graph_nextedge(graph *G, int i, dlobj *e);
dlobj *graph_prevedge(graph *G, int i, dlobj *e);

#endif // GRAPH_T
