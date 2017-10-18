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
  int n; // 節点数
  int m; // 枝数
  dlist **E; // 枝リストの配列
} graph;


graph *graph_input();
graph *graph_input_undirected(FILE *in);
void graph_free(graph *G); // グラフを開放する
void graph_print(graph *G); // グラフの中身を表示する
dlobj *graph_firstedge(graph *G, int i);
dlobj *graph_nextedge(graph *G, int i, dlobj *e);
dlobj *graph_prevedge(graph *G, int i, dlobj *e);
dlobj *dlobj_new(int v, double w);
dlist *dlist_new(void);
void dlist_append(dlist *L, dlobj *r);
#endif // GRAPH_T
