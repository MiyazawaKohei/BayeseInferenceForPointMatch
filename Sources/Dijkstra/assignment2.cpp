#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "dijkstra.h"
using namespace std;

graph *graph_input_from_biparticle(int n,vector<double*> edgecost_between_biparticle)
{
  graph *G;
  double x;
  //File* fin=fopen("graph.txt","r");
  //mymalloc(G, 1);
  G = new graph[1];if ((G)==NULL) {printf("not enough memory\n"); exit(1);}
  //fscanf(fin, "%d %d", &n, &m);
  
  G->n = 2*n+2;
  G->m = n*n+2*n;
  dlobj *obj;
  //mymalloc(G->E, n);
  G->E = new dlist*[G->n];if ((G->E)==NULL) {printf("not enough memory\n"); exit(1);}
	for (int i=0; i<G->n; i++){
		G->E[i] = dlist_new();
	} 
  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      obj = dlobj_new(n+j+1, edgecost_between_biparticle[i][j]);
      dlist_append(G->E[i], obj);
    }
  }
  for (int i=0; i<n; i++) {
    obj = dlobj_new(i+1, 0);
    dlist_append(G->E[2*n], obj);
    obj = dlobj_new(2*n+2, 0);
    dlist_append(G->E[n+i], obj);
  }

  return G;
}
int main(int argc, char *argv[])
{
  graph *G;
  double *dist;
  int *parent;
  int i;
  int n=4;
	vector<double*> edgecost_between_biparticle;

	for(int i=0; i<n; i++){
		edgecost_between_biparticle.push_back(new double [n]);
		for(int j=0; j<n; j++){
			//edgecost_between_biparticle.back()[j]=(i==j?0:1);
			edgecost_between_biparticle[i][j]=(i==j?0.1:1);
		}
	}
  G = graph_input_from_biparticle( n,edgecost_between_biparticle);
  //mymalloc(dist, G->n+1);
  dist = new double[G->n+1];if ((dist)==NULL) {printf("not enough memory\n"); exit(1);}
  //mymalloc(parent, G->n+1);
  parent = new int[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
  Dijkstra(G, 2*n+1, dist, parent);
  for (i=1; i<=G->n; i++) {
    printf("p(%d)=%d dist=%lf\n", i, parent[i], dist[i]);
  }
  delete [] parent;
  delete [] dist;
  graph_free(G);
  return 0;
}

