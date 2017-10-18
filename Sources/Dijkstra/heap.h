#ifndef HEAP_T
#define HEAP_T
typedef struct {
    int value;
    double priority;
} heapdata;

typedef struct {
  int max_size;
  int size;
  heapdata *A;
  int *inv;
} heap;

// heap.c‚Å’è‹`‚³‚ê‚éŠÖ”
void heap_heapify(heap *H, int i);
heap *heap_build(int n, heapdata *A, int max_size);
heapdata heap_extract_min(heap *H);
void heap_insert(heap *H, heapdata x);
void heap_delete(heap *H, int idx);
int heap_exist(heap *H, int idx);
void heap_free(heap *H);
#endif