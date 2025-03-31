#include <stdio.h>
#include <stdlib.h>

typedef struct _heap {
  int currSize;
  int maxSize;
  int* arr;
} Heap;

Heap* createHeap(int* arr, int currSize, int maxSize) {
  Heap* h = (Heap*)malloc(sizeof(Heap));
  h->arr = (int*)malloc(maxSize * sizeof(int));
  for (int i = 0; i < currSize; i++){
    h->arr[i] = arr[i];
  }
  h->maxSize = maxSize;
  h->currSize = currSize;
  return h;
}

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// change > or < will give find min and max
void percolateDown(Heap* h, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < h->currSize && h->arr[left] > h->arr[largest]) {
    largest = left;
  }
  if (right < h->currSize && h->arr[right] > h->arr[largest]) {
    largest = right;
  }
  if (largest != i) {
    swap(&h->arr[i], &h->arr[largest]);
    percolateDown(h, largest);
  }
}

void buildHeap(Heap* h) {
  int n = h->currSize;
  for (int i = (n - 1) / 2; i >= 0; i--) {
    percolateDown(h, i);
  }
  return;
}

void insertHeap(Heap* h, int value) {
  if (h->currSize == h->maxSize) {
    puts("The heap is full, cannot insert.");
    return;
  }

  h->currSize++;
  int i = h->currSize - 1;
  h->arr[i] = value;

  while (i != 0 && h->arr[(i - 1) / 2] < h->arr[i]) {
    swap(&h->arr[i], &h->arr[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

int getMax(Heap* h) {
  if (h->currSize <= 0) {
    puts("The heap is empty, cannot find Max.");
    return -1;
  }
  return h->arr[0];
}

void deleteMax(Heap* h) {
  if (h->currSize <= 0)
    return;

  if (h->currSize == 1) {
    h->currSize--;
    return;
  }
  
  h->arr[0] = h->arr[h->currSize - 1];
  h->currSize--;
  percolateDown(h, 0);
  return;
}

void printHeap(Heap* h) {
  printf("[");
  for (int i = 0; i < h->currSize; i++) {
    printf("%d ", h->arr[i]);
  }
  printf("]\n");
}

// Function to delete an element at a given index
void deleteKey(Heap* h, int index) {
  if (index >= h->currSize) {
    return;
  }
  if (index == h->currSize - 1) {
    h->currSize--;
    return;
  }
  h->arr[index] = h->arr[h->currSize - 1];
  h->currSize--;

  percolateDown(h, index);
}

void freeHeap(Heap* h)
{
  free(h->arr);
  free(h);
}

int main()
{
  int dump[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Heap *h = createHeap(dump, 10, 20);
  buildHeap(h);
  printf("Max Heap array: ");
  printHeap(h);
  printf("Get max value: %d\n", getMax(h));
  deleteMax(h);
  printHeap(h);
  deleteMax(h);
  deleteMax(h);
  deleteMax(h);
  printHeap(h);
  insertHeap(h, 9);
  insertHeap(h, 8);
  insertHeap(h, 7);
  insertHeap(h, 10);
  insertHeap(h, 13);
  insertHeap(h, 14);
  insertHeap(h, 15);
  printHeap(h);
  freeHeap(h);
}
