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
dlobj *dlobj_new(int v, double w);
dlist *dlist_new(void);
dlobj *dlist_search(dlist *L, int v);
void dlist_insert(dlist *L, dlobj *r);
void dlist_delete(dlobj *r);
void dlist_append(dlist *L, dlobj *r);

#endif // GRAPH_T
