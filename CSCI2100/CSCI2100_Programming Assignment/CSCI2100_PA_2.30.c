#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_CHAR 1000005

// node structure
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// stack structure
typedef struct Stack {
	Node* head;
} Stack;

// create a stack
Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));   // assign size to stack
    s->head = NULL; // assign size to head
    return s;
}

// empty stack
void freeStack(Stack* s) {
    Node* n = s->head;  // move top to n
    while (n) { // unless stack is empty
        Node* temp = n->next;   // copy next element to temp
        free(n);    // remove stack top
        n = temp;   // assign new top
    }
    free(s); // free stack
}

// determine if the stack is empty
int isEmpty(Stack *s)
{
    return (s->head == NULL);
}

// find the top value of stack
char top(Stack* s) {
    if(!isEmpty(s))
        return s->head->data;
    else
        return -1;
}

// push element into stack
void Push(Stack *s, char inputdata) {
    Node* n = (Node*)malloc(sizeof(Node));  // assign size to the node
    n->data = inputdata;    // assign value to input
    n->next = s->head;  // assign link
    s->head = n;    // move head pointer
}

// pop element out of stack
void Pop(Stack* s) {
    char temp;   // temp to store data
    Node* toBePopped;   // node to be popped
    if(!isEmpty(s)) {
        temp = s->head->data;   // copy head data to temp
        toBePopped = s->head;   // copy head to node 
        s->head = s->head->next;    // move head to next element
        free(toBePopped);   //remove previous head
        return;
    }
    else
        return;
}

// main function to check if brackets matched
void bcheck(Stack* s, char brackets[]) {
    int replacement = 0;    // no of replacement to be made
    for (int i = 0; brackets[i] != '\0'; i++) {
        if (brackets[i] == '(' || brackets[i] == '[' || brackets[i] == '{' || brackets[i] == '<'){  // if input open
            Push(s, brackets[i]);   // push into stack
        }
        else if (brackets[i] == ')' || brackets[i] == ']' || brackets[i] == '}' || brackets[i] == '>'){ // if input closing
            if (isEmpty(s)) {   // if stack is empty -> invalid
                replacement = -1;   // mark not match
                break;
            }
            else if ((top(s) == '(' && brackets[i] == ')') || (top(s) == '[' && brackets[i] == ']') || (top(s) == '<' && brackets[i] == '>') || (top(s) == '{' && brackets[i] == '}')){ // if brackets match
                Pop(s); // pop head from stack
                continue;
            }
            else {  // if doesn't match
                replacement++;  // need to replace one
                Pop(s); // pop head from stack
                continue;
            }
        }
        else {  // other inputs, skip
            continue;
        }
    }
    if (!isEmpty(s)) {  // after all push/pop, if there is brackets left
        replacement = -1;   // false
    }
    printf("%d\n", replacement);    // print the no. of replacement
}

int main() {
    int cases, i;
    scanf("%d", &cases);    // input no. of cases
    getchar();  // remove newline
    for (i = 0; i < cases; i++){
        Stack* storage = create_stack();    // create stack
        char brackets[Max_CHAR] = "";    // empty brackets array
        scanf("%[^\n]", brackets);
        getchar();  // remove newline
        bcheck(storage, brackets);
        freeStack(storage); // free stack
    }
    return 0;
}
