#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node* next;
} Node;

typedef struct _queue {
	Node* front;
	Node* rear;
} Queue;

Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = (Node*)malloc(sizeof(Node));
	q->front->next = NULL;
	q->rear = q->front;
	return q;
}

int isEmpty(Queue* q) {
	return q->front == q->rear;
}

void enqueue(Queue* q, int input) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->data = input;
	n->next = NULL;
	q->rear->next = n; 
	q->rear = n;
}

void dequeue(Queue *q) {
	if (isEmpty(q))	{
		puts("The queue is empty.");
		return;
	}
	Node *temp = q->front->next;
	q->front->next = temp->next;

	if (q->front->next == NULL)
		q->rear = q->front;

	free(temp);
}

int front(Queue *q) {
	if (isEmpty(q))	{ 
		puts("The queue is empty, there is no front.");
		return -1;
	}
	return q->front->next->data;
}

void freeQueue(Queue *q) {
	while (!isEmpty(q))	{
		dequeue(q);
	}
	free(q->front);
	free(q);
}

void printQueue(Queue *q) {
	if (isEmpty(q)) {
		puts("[ Empty Queue ]");
		return;
	}
	Node *temp = q->front->next;
	printf("[");
	while (temp != NULL) {
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("]\n");
}

int main() {
	Queue *q = createQueue();
	dequeue(q);
	front(q);
	printQueue(q);
	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	enqueue(q, 4);
	enqueue(q, 5);
	printQueue(q);
	dequeue(q);
	dequeue(q);
	printQueue(q);
	enqueue(q, 6);
	enqueue(q, 7);
	printQueue(q);
	dequeue(q);
	printQueue(q);
	enqueue(q, 8);
	enqueue(q, 9);
	enqueue(q, 10);
	while (!isEmpty(q)) {
		printQueue(q);
		printf("Dequeue: %d\n", front(q));
		dequeue(q);
	}
	freeQueue(q);
}
