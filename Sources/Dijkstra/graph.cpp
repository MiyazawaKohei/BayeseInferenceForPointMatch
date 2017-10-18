#include <stdlib.h>
#include "graph.h"

//#define mymalloc(p,n) {p = malloc((n)*sizeof(*p));if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

dlobj *dlobj_new(int v, double w){
    dlobj *new_obj;
    //mymalloc(new_obj, 1);
    new_obj = new dlobj[1];if ((new_obj)==NULL) {printf("not enough memory\n"); exit(1);}
    new_obj->next = NULL;
    new_obj->prev = NULL;
    new_obj->v = v;
    new_obj->w = w;
    return new_obj;
}

dlist *dlist_new(void){
    dlist *new_list;
    //mymalloc(new_list, 1);
    new_list = new dlist[1];if ((new_list)==NULL) {printf("not enough memory\n"); exit(1);}
    new_list->nil = dlobj_new(0, 0);
    new_list->nil->next = new_list->nil;
    new_list->nil->prev = new_list->nil;
    return new_list;
}

dlobj *dlist_search(dlist *L, int v){
    dlobj *now = L->nil->next;
    while(now != L->nil){
        if(now->v == v){
            return now;
        }
        now = now->next;
    }
    return NULL;
}

void dlist_insert(dlist *L, dlobj *r){
    L->nil->next->prev = r;
    r->next = L->nil->next;
    r->prev = L->nil;
    L->nil->next = r;
    return;
}

void dlist_append(dlist *L, dlobj *r){
    r->next = L->nil;
    L->nil->prev->next = r;
    r->prev = L->nil->prev;
    L->nil->prev = r;
    return;
}

void dlist_delete(dlist *L, dlobj *r){
    r->prev->next = r->next;
    r->next->prev = r->prev;
    return;
}

void dlist_free(dlist *L){
    dlobj *now = L->nil->next;
    dlobj *tmp;
    while(now != L->nil){
        tmp = now->next;
        delete []now;
        now = tmp;
    }
    delete[] L->nil;
    delete[] L;
    return;
}

graph *graph_input()
{
  graph *G;
  int n, m;
  int j;
  double x;
  //File* fin=fopen("graph.txt","r");
  //mymalloc(G, 1);
  G = new graph[1];if ((G)==NULL) {printf("not enough memory\n"); exit(1);}
  //fscanf(fin, "%d %d", &n, &m);
  scanf("%d %d", &n, &m);
  
  G->n = n;
  G->m = m;

  //mymalloc(G->E, n);
  G->E = new dlist*[n];if ((G->E)==NULL) {printf("not enough memory\n"); exit(1);}
  for (int i=0; i<n; i++) {
    dlobj *obj;
    G->E[i] = dlist_new();
    
    while (1) {
      if (scanf("%d", &j) < 1) break;
      if (j == -1) break;
      if (scanf("%lf", &x) < 1) break;
      obj = dlobj_new(j, x);
      dlist_append(G->E[i], obj);
    }
  }
  return G;
}

graph *graph_input_undirected(FILE *fin)
{
  graph *G;
  int n, m;
  int i;

  //mymalloc(G, 1);
  G = new graph[1];if ((G)==NULL) {printf("not enough memory\n"); exit(1);}
  fscanf(fin, "%d %d", &n, &m);
  G->n = n;
  G->m = m*2;

  //mymalloc(G->E, n);
  G->E = new dlist*[1];if ((G->E)==NULL) {printf("not enough memory\n"); exit(1);}
  
  for (i=1; i<=n; i++) {
    G->E[i-1] = dlist_new();
  }

  for (i=1; i<=n; i++) {
    dlobj *obj;
    while (1) {
      int j;
      double x;
      if (fscanf(fin, "%d", &j) < 1) break;
      if (j == -1) break;
      if (fscanf(fin, "%lf", &x) < 1) break;
      obj = dlobj_new(j, x);
      dlist_append(G->E[i-1], obj);
      obj = dlobj_new(i, x);
      dlist_append(G->E[j-1], obj);
    }
  }

  return G;
}

void graph_free(graph *G)
{
  int i;
  for (i=0; i<G->n; i++) {
    dlist_free(G->E[i]);
  }
  delete []G->E;
  delete []G;
}

dlobj *graph_firstedge(graph *G, int i)
{
  dlobj *obj;
  i--;
  obj = G->E[i]->nil;
  if (obj->next == obj) return NULL;
  return obj->next;
}

dlobj *graph_nextedge(graph *G, int i, dlobj *e)
{
  i--;
  e = e->next;
  if (e == G->E[i]->nil) return NULL;
  return e;
}

dlobj *graph_prevedge(graph *G, int i, dlobj *e)
{
  i--;
  e = e->prev;
  if (e == G->E[i]->nil) return NULL;
  return e;
}

void graph_print(graph *G)
{
  int i;
  dlobj *edge;
  printf("*************************************************\n");
  printf("number of nodes = %d\n", G->n);
  printf("number of edges = %d\n", G->m);
  for (i=1; i<=G->n; i++) {
    edge = graph_firstedge(G, i);
    if (edge != NULL) {
      printf("node %d:", i);
      while (edge != NULL) {
        printf(" (%d:%lf)", edge->v, edge->w);
        edge = graph_nextedge(G, i, edge);
      }
      printf("\n");
    }
  }
  printf("*************************************************\n\n");
}

