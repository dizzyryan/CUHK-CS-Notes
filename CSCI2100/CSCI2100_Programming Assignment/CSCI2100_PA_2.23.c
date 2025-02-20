#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Max_CHAR 260

// node structure
typedef struct Node {
    int data;
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
    return (s->head==NULL);
}

// find the top value of stack
int top(Stack* s) {
    if(!isEmpty(s))
        return s->head->data;
    else
        return -1;
}

// push element into stack
void Push(Stack *s, int inputdata) {
    Node* n = (Node*)malloc(sizeof(Node));  // assign size to the node
    n->data = inputdata;    // assign value to input
    n->next = s->head;  // assign link
    s->head = n;    // move head pointer
}

// pop element out of stack
int Pop(Stack* s) {
    int temp;   // temp to store data
    Node* toBePopped;   // node to be popped
    if(!isEmpty(s)) {
        temp = s->head->data;   // copy head data to temp
        toBePopped = s->head;   // copy head to node 
        s->head = s->head->next;    // move head to next element
        free(toBePopped);   //remove previous head
        return temp;    // return original head value
    }
    else
        return 0;
}

// recursively find factorial
int factorial(int n){
    if (n == 1 || n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

// main function to evaluate postfix expression
void evaluate(Stack* s, char postfix[]) {
    char* temp = strtok(postfix, " ");  // find expression
    while (temp != NULL){
        if (isdigit(temp[0]) || (temp[0] == '-' && isdigit(temp[1]))) { // if element is digit 
            Push(s, atoi(temp));    // push digit to stack
        }
        else {  // if operators
            int a, b;   // a <operator> b
            if (!isEmpty(s)) { // if still have operands
                if (*temp == '+'){  // addition
                    b = Pop(s);
                    a = Pop(s);
                    Push(s, a + b); // put value back to stack top
                }
                if (*temp == '-'){  // subtraction
                    b = Pop(s);
                    a = Pop(s);
                    Push(s, a - b); // put value back to stack top
                }
                if (*temp == '*'){ // multiplication
                    b = Pop(s);
                    a = Pop(s);
                    Push(s, a * b); // put value back to stack top
                }
                if (*temp == '/'){  // division
                    b = Pop(s);
                    a = Pop(s);
                    if (b == 0) {   // if divided by zero
                        printf("division by zero\n");
                        return; // false
                    }
                    Push(s, a / b); // put value back to stack top
                }
                if (*temp == '!'){  // factorial
                    a = Pop(s);
                    if (a < 0) {    // if factorial of a negative number
                        printf("factorial of an negative number\n");
                        return;
                    }
                    Push(s, factorial(a));  // put value back to stack top
                }
            }
            else    // if no operands
                break;  // 
        }
        temp = strtok(NULL, " ");   // update temp
    }
    printf("%d\n", Pop(s)); // print final value
}

int main() {
    int cases, i;
    scanf("%d", &cases);    // input no. of cases
    getchar();  // remove newline
    for (i = 0; i < cases; i++){
        Stack* expressionStore = create_stack();    // create stack
        char postfix[Max_CHAR] = "";    // empty postfix array
        scanf("%[^\n]", postfix);
        getchar();  // remove newline
        evaluate(expressionStore, postfix);
        freeStack(expressionStore); // free stack
    }
    return 0;
}
