#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define SMALLER(x,y) ((x).priority < (y).priority)

///////////////////////////////////////////////////////////////////////////
// ヒープ
// ヒープに格納される要素は 0 から n-1 までの番号がついている
// 番号 i の要素はヒープの添字 inv[i] の配列に格納されている
// A[j].value (j=1..n) は要素の番号を格納している
// inv[A[j].value] = j が常に成り立つ
// inv[i] == -1 のときは，番号 i の要素はヒープ中に存在しない
///////////////////////////////////////////////////////////////////////////

//#define mymalloc(p,n) {p = malloc((n)*sizeof(*p));if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

#define LEFT(i) (2*i)
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) (i/2)

static void heap_swap(heap *H, int x, int y)
{
  heapdata tmp;

  tmp = H->A[x];
  H->A[x] = H->A[y];
  H->A[y] = tmp;

  H->inv[H->A[x].value] = x;
  H->inv[H->A[y].value] = y;

}

void heap_heapify(heap *H, int i)
{
  int l, r, largest, size;
  heapdata *A;

  A = H->A;
  size = H->size;

  l = LEFT(i);   r = RIGHT(i);
  if (l <= size && SMALLER(A[l], A[i])) largest = l; // A[i] と左の子で大きい
  else  largest = i;                                           // 方をlargestに
  if (r <= size && SMALLER(A[r], A[largest]))        // 右の子の方が大きい
    largest = r;
  if (largest != i) {                                                          
    heap_swap(H, i, largest); // A[i]を子供と入れ替える
    heap_heapify(H, largest);
  }
}

heap *heap_build(int n, heapdata *A, int max_size)
{
  int i;
  heap *H;
  //mymalloc(H, 1);
  H = new heap[1];if ((H)==NULL) {printf("not enough memory\n"); exit(1);}
  
  H->max_size = max_size;
  H->size = n;
  H->A = A;

  //mymalloc(H->inv, max_size);
  H->inv = new int[1];if ((H->inv)==NULL) {printf("not enough memory\n"); exit(1);}
  
  for (i=0; i<max_size; i++) H->inv[i] = -1;

  for (i = H->size/2; i >= 1; i--) {
    heap_heapify(H,i);
  }
  return H;
}


heapdata heap_extract_min(heap *H)  // O(lg n) 時間
{
  heapdata MIN, *A;

  A = H->A;

  if (H->size < 1) {
    printf("ERROR ヒープのアンダーフロー\n");
    exit(1);
  }

  MIN = A[1];
  H->inv[MIN.value] = -1; // MINを削除する

  A[1] = A[H->size]; // 最後の値を根に持っていく
  H->inv[H->A[1].value] = 1;

  H->size = H->size - 1;
  heap_heapify(H,1);
  return MIN;
}

void heap_insert(heap *H, heapdata x)  // O(lg n) 時間
{
  heapdata *A;

  A = H->A;
  int i;

  H->size = H->size + 1;
  if (H->size > H->max_size) {
    printf("ERROR ヒープのオーバーフロー\n");
    exit(1);
  }

  i = H->size;
  A[i] = x;
  H->inv[A[i].value] = i;
  while (i > 1 && SMALLER(A[i],A[PARENT(i)])) {
    heap_swap(H, i, PARENT(i));
    i = PARENT(i);
  }
}

void heap_delete(heap *H, int idx)  // 番号が idx の要素を削除する
{
  int i, *index;

  i = H->inv[idx];
  if (i < 1 || i > H->max_size) {
    printf("ERROR 範囲エラー (%d,%d)\n",i,H->max_size);
    exit(1);
  }

  while (i > 1) {
    H->A[i] = H->A[PARENT(i)];
    H->inv[H->A[i].value] = i;
    i = PARENT(i);
  }
  H->A[1] = H->A[H->size];
  H->inv[H->A[1].value] = 1;
  H->size = H->size - 1;
  heap_heapify(H,1);
  H->inv[idx] = -1;
}

int heap_exist(heap *H, int idx) // 番号 idx の要素が存在すれば 1 を返す
{
  if (H->inv[idx] != -1) return 1;
  else return 0;
}


void heap_free(heap *H)
{
  free(H);
}
