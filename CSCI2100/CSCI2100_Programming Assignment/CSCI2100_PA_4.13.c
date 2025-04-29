#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int *array;
	int size;
	int maxSize;
} Heap;

Heap *createHeap(int maxSize) {
	Heap *h = (Heap *)malloc(sizeof(Heap));
	h->size = 0;
	h->maxSize = maxSize;
	h->array = (int *)malloc(maxSize * sizeof(int));
	return h;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// change > or < will give find min and max
void percolateDown(Heap *heap, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < heap->size && heap->array[left] > heap->array[largest]) {
		largest = left;
	}

	if (right < heap->size && heap->array[right] > heap->array[largest]) {
		largest = right;
	}

	if (largest != i) {
		swap(&heap->array[i], &heap->array[largest]);
		percolateDown(heap, largest);
	}
}

// Function to insert a new value into the heap
void insertHeap(Heap *heap, int value) {
	if (heap->size == heap->maxSize) {
		if (value < heap->array[0])	{
			heap->array[0] = value;
			percolateDown(heap, 0);
		}
		return;
	}

	heap->size++;
	int i = heap->size - 1;
	heap->array[i] = value;

	// Fix the heap property if it is violated
	while (i != 0 && heap->array[(i - 1) / 2] < heap->array[i])	{
		swap(&heap->array[i], &heap->array[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

int getKth(Heap *heap, int k) {
	if (heap->size <= 0) {
		return -1;
	}
	return heap->array[0];
}

void freeHeap(Heap *h) {
	free(h->array);
	free(h);
}

int main() {
	int k, x;
	scanf("%d", &k);
	getchar();
	char command;
	Heap *elements = createHeap(k);
	while (1) {
		command = getchar();
		if (command == 'S')	{
			break;
		}
		else if (command == 'I') {
			scanf("%d", &x);
			insertHeap(elements, x);
			continue;
		}
		else if (command == 'O') {
			printf("%d\n", getKth(elements, k));
		}
	}
	freeHeap(elements);
	return 0;
}
