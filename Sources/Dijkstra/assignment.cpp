#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "dijkstra.h"
using namespace std;
graph *graph_input_from_biparticle(int n,vector<double*> edgecost_between_biparticle)
{
  graph *G;
  int j;
  double x;
  dlobj *obj;
  G = new graph[1];if ((G)==NULL) {printf("not enough memory\n"); exit(1);}
  
  G->n = 2*n+2;
  G->m = n*n+2*n;
  G->E = new dlist*[G->n];if ((G->E)==NULL) {printf("not enough memory\n"); exit(1);}
  for (int i=0; i<n; i++) {
    
    G->E[i] = dlist_new();
    for(int j=0; j<n; j++) {
      obj = dlobj_new(n+j+1, edgecost_between_biparticle[i][j]);
      dlist_append(G->E[i], obj);
    }
  }
  G->E[2*n] = dlist_new();  //start point
  G->E[2*n+1] = dlist_new(); //goal point
  for (int i=0; i<n; i++) {
    obj = dlobj_new(i+1, 0);
    dlist_append(G->E[2*n], obj);
    obj = dlobj_new(2*n+2, 0);
    G->E[n+i] = dlist_new();
    dlist_append(G->E[n+i], obj);
  }
  return G;
}


int main(){
  int n=10;
	vector<double*> edgecost_between_biparticle;
	graph *G;
  double *dist;
	int *parent;
  
	for(int i=0; i<n; i++){
		edgecost_between_biparticle.push_back(new double [n]);
		for(int j=0; j<n; j++){
			edgecost_between_biparticle.back()[j]=1;//(i==j?0:1);
		}
	}
	G=graph_input_from_biparticle(n,edgecost_between_biparticle);
	dist = new double[G->n+1];if ((dist)==NULL) {printf("not enough memory\n"); exit(1);}
  parent = new int[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
  

	Dijkstra(G, 2*n+1, dist, parent);
	for (int i=1; i<=G->n; i++) {
    printf("p(%d)=%d dist=%lf\n", i, parent[i], dist[i]);
  }
  delete [] parent;
  delete [] dist;
  graph_free(G);
  return 0;
}