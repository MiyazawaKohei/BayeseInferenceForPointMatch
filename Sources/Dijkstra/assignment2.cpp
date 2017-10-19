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
void FlipEdges(int n, graph *G, int *parent, dlobj **fromedge){
	int varticlenow=2*n+2;
	dlobj *obj;
	while(parent[varticlenow]!=-1){
		printf("%d %d\n",varticlenow,parent[varticlenow]);
		obj = dlobj_new(parent[varticlenow], -(fromedge[varticlenow]->w));
    dlist_append(G->E[varticlenow-1], obj);
		dlist_delete(fromedge[varticlenow]);
		varticlenow=parent[varticlenow];
	}
}
int main(int argc, char *argv[])
{
  graph *G;
  double *dist;
  int *parent;
  dlobj** fromedge;
  int i;
  int n=4;
	vector<double*> edgecost_between_biparticle;

	for(int i=0; i<n; i++){
		edgecost_between_biparticle.push_back(new double [n]);
		for(int j=0; j<n; j++){
			//edgecost_between_biparticle.back()[j]=(i==j?0:1);
			edgecost_between_biparticle[i][j]=(i==j?i:100);
		}
	}
  G = graph_input_from_biparticle( n,edgecost_between_biparticle);
  dist = new double[G->n+1];if ((dist)==NULL) {printf("not enough memory\n"); exit(1);}
  parent = new int[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
  fromedge = new dlobj*[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
   
  Dijkstra(G, 2*n+1, dist, parent,fromedge);
  for (i=1; i<=G->n; i++) {
    printf("p(%d)=%d dist=%lf,", i, parent[i], dist[i]);
    printf("p(%d)=%lf\n", i, (fromedge[i]!=NULL?fromedge[i]->w:-1));
  }
  FlipEdges(n,G,parent,fromedge);
  delete [] fromedge;
  Dijkstra(G, 2*n+1, dist, parent,fromedge);
  for (i=1; i<=G->n; i++) {
    printf("p(%d)=%d dist=%lf,", i, parent[i], dist[i]);
    printf("p(%d)=%lf\n", i, (fromedge[i]!=NULL?fromedge[i]->w:-1));
  }
  delete [] parent;
  delete [] dist;
  graph_free(G);
  return 0;
}

