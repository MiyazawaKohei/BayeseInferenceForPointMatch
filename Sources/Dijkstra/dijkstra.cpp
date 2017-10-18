#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"
/*
#ifndef mymalloc
#define mymalloc(TYPE p,TYPE2 n) {p = new Type<p> [n];if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}
#endif
*/
#define INFINITY 9999999999

void Dijkstra(graph *G, int s, double *dist, int *parent)
{
  int n,m;
  int i;
  heap *H;
  heapdata *A;
  heapdata v, j;

  n = G->n;  m = G->m;
  for (i=1; i<=n; i++) {
    dist[i] = INFINITY;
    parent[i] = -1;
  }
  dist[s] = 0.0;
  //mymalloc(A, n+1);
  A = new heapdata[n+1];if ((A)==NULL) {printf("not enough memory\n"); exit(1);}
  H = heap_build(0, A, n+1);
  for (i=1; i<=n; i++) {
    v.value = i;  v.priority = dist[i];
    heap_insert(H, v);
  }

  while (H->size > 0) {
    dlobj *edge;
    v = heap_extract_min(H);
    printf("%d",v.value);
    edge = graph_firstedge(G, v.value); // v ‚©‚ço‚Ä‚¢‚éÅ‰‚Ì}
    while (edge != NULL) {
      j.value = edge->v; // edge ‚Í (v,j)
      if (heap_exist(H,j.value)) { // —×Ú“_ j ‚ª bar(S) ‚É“ü‚Á‚Ä‚¢‚é
        if (dist[j.value] > dist[v.value] + edge->w) {
          heap_delete(H, j.value); // dist[j] ‚ğXV‚·‚é‚Ì‚Åˆê’Uíœ
          dist[j.value] = dist[v.value] + edge->w; // j ‚Ü‚Å‚ÌÅ’Z˜H’·‚ğXV‚·‚é
          parent[j.value] = v.value; // Å’Z˜Hã‚Å j ‚Ì‘O‚Ì“_‚Í v
          j.priority = dist[j.value];
          heap_insert(H, j);
        }
      }
      edge = graph_nextedge(G, v.value, edge); // v ‚©‚ço‚Ä‚¢‚éŸ‚Ì}
    }
  }
  free(A);
  heap_free(H);
  return ;
}


int main(int argc, char *argv[])
{
  graph *G;
  double *dist;
  int *parent;
  int i;
  //FILE *fin=fopen("graph.txt","r");
  //if(fin==NULL)    {printf("File is not found"); return 0;}
  for(int i=0; i<5; i++){
    printf("%d",i);
  }
  G = graph_input();
  //mymalloc(dist, G->n+1);
  printf("4");
  dist = new double[G->n+1];if ((dist)==NULL) {printf("not enough memory\n"); exit(1);}
  //mymalloc(parent, G->n+1);
  parent = new int[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
  printf("4");
  Dijkstra(G, 1, dist, parent);
  printf("4");
  for (i=1; i<=G->n; i++) {
    printf("p(%d)=%d dist=%lf\n", i, parent[i], dist[i]);
  }
  delete [] parent;
  delete [] dist;
  graph_free(G);
  return 0;
}

