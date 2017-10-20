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

void AssignmentfromMatrix(vector<double*> edgecost_between_biparticle,
  vector<int>* sigma)
{
  graph *G;
  double *dist;
  int *parent;
  dlobj** fromedge;
  int i;
  int n=edgecost_between_biparticle.size();
  
	/*for(int i=0; i<n; i++){
		edgecost_between_biparticle.push_back(new double [n]);
		for(int j=0; j<n; j++){
			//edgecost_between_biparticle.back()[j]=(i==j?0:1);
			edgecost_between_biparticle[i][j]=(i+j)%3;//(i==j?i+1:100);
		}
	}*/
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      printf("%lf",edgecost_between_biparticle[i][j]);//(i==j?i+1:100);
    }
    printf("\n");
  }

  G = graph_input_from_biparticle( n,edgecost_between_biparticle);
  dist = new double[G->n+1];if ((dist)==NULL) {printf("not enough memory\n"); exit(1);}
  parent = new int[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
  
  while(1){ 
  	for(int i=0; i<2*n+2; i++){
	  	dlobj* obj=G->E[i]->nil->next;
	  	while(obj!=G->E[i]->nil){
	  		printf("%d %d\n",i,obj->v);
	  		obj=obj->next;
	  	}
  	}
  	fromedge = new dlobj*[G->n+1];if ((parent)==NULL) {printf("not enough memory\n"); exit(1);}
	  Dijkstra(G, 2*n+1, dist, parent,fromedge);
	  if(dist[2*n+2]>10000) break;
	  for (i=1; i<=G->n; i++) {
	    printf("p(%d)=%d dist=%lf,", i, parent[i], dist[i]);
	    printf("p(%d)=%lf\n", i, (fromedge[i]!=NULL?fromedge[i]->w:-1));
	  }
	  FlipEdges(n,G,parent,fromedge);
	  delete [] fromedge;
  }
  for(int i=0; i<2*n+2; i++){
  	dlobj* obj=G->E[i]->nil->next;
  	while(obj!=G->E[i]->nil){
  		printf("%d %d\n",i,obj->v);
  		obj=obj->next;
  	}
  }
  for(int i=n; i<2*n; i++){
  	printf("%d %d\n",i+1-n,G->E[i]->nil->next->v);
    (*sigma)[G->E[i]->nil->next->v-1]=i-n;
  }


  delete [] parent;
  delete [] dist;
  graph_free(G);
}

