#include <stdio.h>
#include <stdlib.h>

typedef struct _queue {
	int* data;
	int front;
	int rear;
	int currSize;
	int maxSize;
} Queue;

Queue* createQueue(int maxSize) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = (int*)malloc(maxSize * sizeof(int));
	q->front = -1;
	q->rear = -1;
	q->maxSize = maxSize;
	q->currSize = 0;
	return q;
}

int isEmpty(Queue* q) {
	return (q->currSize == 0);
}

int isFull(Queue* q) {
	return (q->currSize >= q->maxSize);
}

void enqueue(Queue* q, int data) {
	if (isFull(q)) {
		puts("The queue is full.");
		return;
	}
	if (isEmpty(q)) {
		q->front = 0;
	}
	q->rear = (q->rear + 1) % q->maxSize;
	q->data[q->rear] = data;
	q->currSize++;
}

void dequeue(Queue* q) {
	if (isEmpty(q))	{
		puts("The queue is empty.");
		return;
	}
	if (q->front == q->rear) {
		q->front = -1;
		q->rear = -1;
	}
	else {
        q->front = (q->front + 1) % q->maxSize;
    }
	q->currSize--;
	return;
}

int front(Queue* q) {
	if (isEmpty(q))	{
		puts("The queue is empty, there is no front.");
		return -1;
	}
	return q->data[q->front];
}

void printQueue(Queue* q) {
	if (isEmpty(q)) {
		puts("[ Empty Queue ]");
		return;
	}
	printf("[");
	for (int i = 0; i < q->currSize; i++) {
        int index = (q->front + i) % q->maxSize;
        printf("%d-> ", q->data[index]);
    }
	printf("]\n");
}

void freeQueue(Queue *q) {
	free(q->data);
	free(q);
}

int main() {
	Queue* q = createQueue(10);
	dequeue(q);
	printQueue(q);
	front(q);
	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	enqueue(q, 5);
	printQueue(q);
	dequeue(q);
	dequeue(q);
	printQueue(q);
	enqueue(q, 6);
	enqueue(q, 7);
	enqueue(q, 8);
	enqueue(q, 9);
	enqueue(q, 10);
	enqueue(q, 11);
	enqueue(q, 12);
	printQueue(q);
	dequeue(q);
	dequeue(q);
	printQueue(q);
	enqueue(q, 9);
	enqueue(q, 10);
	while (!isEmpty(q)) {
		printQueue(q);
		printf("dequeue: %d\n", front(q));
		dequeue(q);
	}
	freeQueue(q);
	return 0;
}
