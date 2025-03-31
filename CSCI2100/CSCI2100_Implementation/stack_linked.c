#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node* next;
} Node;

typedef struct _stack {
	Node* head;
} Stack;

Stack* createStack() {
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->head = malloc(sizeof(Node));
	s->head->next = NULL;
	return s;
}

void freeStack(Stack* s) {
	Node* n = s->head;
	while (n) {
		Node* temp = n->next;
		free(n);
		n = temp;
	}
	free(s);
}

int isEmpty(Stack* s) {
	return (s->head->next == NULL);
}

int top(Stack* s) {
	if (!isEmpty(s))
		return s->head->next->data;
	else {
		puts("The stack is empty, no top.");
		return -1;
	}
}

void Push(Stack* s, int input) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->data = input;
	n->next = s->head->next;
	s->head->next = n;
}

void Pop(Stack* s) {
	// int temp;
	Node* toBePopped;
	if (!isEmpty(s)) {
		// temp = s->head->next->data;
		toBePopped = s->head->next;
		s->head->next = s->head->next->next;
		free(toBePopped);
		return;
	}
	else {
		puts("The stack is empty, cannot pop.");
		return;
	}
}

void printStack(Stack* s) {
	Node* temp = s->head->next;
	printf("[");
	while (temp != NULL) {
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("]\n");
}

int main(void) {
	Stack* stack = createStack();
	top(stack);
	Pop(stack);
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