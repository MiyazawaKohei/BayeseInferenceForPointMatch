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
  	G->E[n+i] = dlist_new();
  } 
  G->E[2*n] = dlist_new();  //start point
  G->E[2*n+1] = dlist_new(); //goal point
  for (int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
    	if(edgecost_between_biparticle[i][j]>=0){
      		obj = dlobj_new(n+j+1, edgecost_between_biparticle[i][j]);
    		dlist_append(G->E[i], obj);
      	}else{
      		obj = dlobj_new(i+1, edgecost_between_biparticle[i][j]);
      		dlist_append(G->E[n+j], obj);
      	}
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

void FlipEdge(int n, vector<double*>* edgecost_between_biparticle, int* parent){
	int varticleNonow=2*n+2;
	int i;
	while(varticleNonow!=2*n+1){
		printf("%d %d",varticleNonow,parent[varticleNonow]);
		scanf("%d",&i);
		if(parent[varticleNonow]!=2*n+1)return;
		if(varticleNonow!=2*n+2 && parent[varticleNonow]!=2*n+1){
			if(parent[varticleNonow]<varticleNonow){
				printf("t");
				scanf("%d",&i);
				*edgecost_between_biparticle[parent[varticleNonow]-1][varticleNonow-n-1]*=-1;
			}else{
				*edgecost_between_biparticle[varticleNonow-1][parent[varticleNonow]-n-1]*=-1;
			}
		}
		varticleNonow=parent[varticleNonow];
	}
	return;
}
int main(){
  int n=10;
	vector<double*> edgecost_between_biparticle;
	graph *G;
  double *dist;
	int *parent;
  dist = new double[2*n+2+1];if ((dist)==NULL) {printf("not enough memory\n"); exit(1);}
  parent = new int[2*n+2+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
  

	for(int i=0; i<n; i++){
		edgecost_between_biparticle.push_back(new double [n]);
		for(int j=0; j<n; j++){
			//edgecost_between_biparticle.back()[j]=(i==j?0:1);
			edgecost_between_biparticle[i][j]=(i==j?0.1:1);
		}
	}

	while(1){
		G=graph_input_from_biparticle(n,edgecost_between_biparticle);
		Dijkstra(G, 2*n+1, dist, parent);
		if(dist[2*n+1]>10000) break;
		for (int i=1; i<=G->n; i++) {
	    printf("p(%d)=%d dist=%lf\n", i, parent[i], dist[i]);
	 	 }

		int varticleNonow=2*n+2;
		printf("%d",n);
		while(varticleNonow!=2*n+1){
			if(varticleNonow!=2*n+2 && parent[varticleNonow]!=2*n+1){
				if(parent[varticleNonow]<varticleNonow){
					edgecost_between_biparticle[parent[varticleNonow]-1][varticleNonow-n-1]*=-1;
				}else{
					edgecost_between_biparticle[varticleNonow-1][parent[varticleNonow]-n-1]*=-1;
				}
			}
			varticleNonow=parent[varticleNonow];
		}
		graph_free(G);
		//G=graph_input_from_biparticle(n,edgecost_between_biparticle);
	}

  delete [] parent;
  delete [] dist;
  return 0;
}