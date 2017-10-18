#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"
#include "dijkstra.h"
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
    edge = graph_firstedge(G, v.value); // v ����o�Ă���ŏ��̎}
    while (edge != NULL) {
      j.value = edge->v; // edge �� (v,j)
      if (heap_exist(H,j.value)) { // �אړ_ j �� bar(S) �ɓ����Ă���
        if (dist[j.value] > dist[v.value] + edge->w) {
          heap_delete(H, j.value); // dist[j] ���X�V����̂ň�U�폜
          dist[j.value] = dist[v.value] + edge->w; // j �܂ł̍ŒZ�H�����X�V����
          parent[j.value] = v.value; // �ŒZ�H��� j �̑O�̓_�� v
          j.priority = dist[j.value];
          heap_insert(H, j);
        }
      }
      edge = graph_nextedge(G, v.value, edge); // v ����o�Ă��鎟�̎}
    }
  }
  free(A);
  heap_free(H);
  return ;
}

/*
int main(int argc, char *argv[])
{
  graph *G;
  double *dist;
  int *parent;
  int i;
  G = graph_input();
  //mymalloc(dist, G->n+1);
  dist = new double[G->n+1];if ((dist)==NULL) {printf("not enough memory\n"); exit(1);}
  //mymalloc(parent, G->n+1);
  parent = new int[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
  Dijkstra(G, 2, dist, parent);
  for (i=1; i<=G->n; i++) {
    printf("p(%d)=%d dist=%lf\n", i, parent[i], dist[i]);
  }
  delete [] parent;
  delete [] dist;
  graph_free(G);
  return 0;
}*/

