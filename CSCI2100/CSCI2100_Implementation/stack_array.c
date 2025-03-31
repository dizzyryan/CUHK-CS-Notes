#include <stdio.h>
#include <stdlib.h>

typedef struct _stack {
	int* data;
	int top;
	int size;
} Stack;

Stack* createStack(int size) {
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->size = size;
	s->top = -1;
	s->data = (int*)malloc(size * sizeof(int));
	return s;
}

void freeStack(Stack* s) {
	if (s) {
		free(s->data);
		free(s);
	}
}

int isFull(Stack* s) {
	return s->top >= s->size - 1;
}

int isEmpty(Stack* s) {
	return s->top < 0;
}

int Push(Stack* s, int x) {
	if (isFull(s)) {
		puts("The stack is full, cannot push.");
		return 0;
	}
	s->data[++(s->top)] = x;
	return 1;
}

int Pop(Stack* s) {
	if (isEmpty(s)) {
		puts("The stack is empty, cannot pop.");
		return -1;
	}
	return s->data[(s->top)--];
}

int top(Stack* s) {
	if (isEmpty(s)) {
		puts("The stack is empty, no top element.");
		return -1;
	}
	return s->data[s->top];
}

void printStack(Stack* s) {
	if (isEmpty(s)) {
		puts("[Empty Stack]");
		return;
	}
	printf("[");
	for (int i = s->top; i >= 0; i--){
		printf("%d->", s->data[i]);
	}
	printf("]\n");
}

int main() {
	Stack* stack = createStack(10);
	Pop(stack);
	printStack(stack);
	top(stack);
	Push(stack, 1);
	Push(stack, 2);
	Push(stack, 3);
	Push(stack, 4);
	Push(stack, 5);
	Push(stack, 6);
	printStack(stack);
	Pop(stack);
	Pop(stack);
	Pop(stack);
	printStack(stack);
	Push(stack, 7);
	Push(stack, 8);
	Push(stack, 9);
	Push(stack, 10);
	while (!isEmpty(stack)) {
		printStack(stack);
		printf("Popped: %d\n", top(stack));
		Pop(stack);
	}
	freeStack(stack);
	return 0;
}
