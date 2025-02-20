#include <stdio.h>
#include <stdlib.h>
#define Max_STR 500000

// node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// create new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue)); // malloc -> assign size of queue to new queue
    q->front = q->rear = NULL;  // make front and rear NULL
    return q; // return the created queue
}

// check if queue is empty
int isEmpty(Queue* q)
{
    if (q->front == NULL && q->rear == NULL)  // if front and rear is empty -> queue is empty
        return 1;
    return 0;
}

// push elements into queue
void enqueue(Queue *q, int inputdata)
{
    Node* n = (Node*) malloc(sizeof(Node)); // new node to be added into queue
    n->data = inputdata;  // assign data to new element
    n->next = NULL; // make new element link to NULL
    if (isEmpty(q)){  // if q is empty, front == rear == new element
        q->front = q->rear = n;
        return;
    }
    q->rear->next = n;  // link previous 'last element' to new 'last element'
    q->rear = n;  // move rear pointer to last element
}

// pop first elements out of queue
void dequeue(Queue* q)
{
    if (isEmpty(q)){  // if queue empty, nothing to pop
        return;
    }
    Node* temp = q->front;  // store front as temporary
    q->front = q->front->next;  // move front pointer to the next element

    if (q->front == NULL)   // if there is only one element
        q->rear = NULL; // make rear null

    free(temp); // remove front
}

// print front
int front(Queue* q)
{
    if (isEmpty(q)) {   // if queue empty, nothing to print
        return 0;
    }
    return q->front->data;  // return front data
}

// empty queue
void emptyQueue(Queue* q) {
    while (!isEmpty(q)) {   // while queue not empty, keep deleting elements
        dequeue(q); // pop front out of element
    }
    free(q);    // free queue
}

// main function, used to arrange carts in given sequence
void arrangeCart(Queue* q, int carts, int seq[], char printStr[]) {
    int i, j = 1; // j for initial state(1->n), i for counter
    int possible = 1;   // whether it is possible to arrange the carts or not, initialize to yes
    int index = 0;
    for (i = 0; i < carts; i++){
        if (j <= carts) {   // if initial numbers is less than cart number
            while (j <= carts && seq[i] > j){ // if current cart to be put is larger than initial state
                enqueue(q, j);  // enqueue
                printStr[index++] = 'I'; // and add the char to indicate enqueue
                j++;    // increment, then go back to check if this cart could go straight
            }
            if (j <= carts && seq[i] == j){   // if current initial number equals sequence
                printStr[index++] = 'S';  // go straight
                j++;    // move to next initial number
                continue;   // back to original loop
            }
            else if (seq[i] < j){ // if current sequence is less than initial -> enqueued before
                if (front(q) == seq[i]){    // check if front is the desire sequence
                    printStr[index++] = 'O';  // add char to indicate dequeue
                    dequeue(q);
                    continue;   // back to original loop
                }
                else {  // if top is not the desire seq, impossible to do arrangement
                    printf("Impossible\n");
                    possible = 0;
                    break;  // leave the loop
                }
            }
        }
        else{ // if j > cart, i.e. all initial carts are enqueued
            if (front(q) == seq[i]){    // if front is the desired cart
                printStr[index++] = 'O';  // indicate dequeue
                dequeue(q);
                continue;   // back to original loop
            }
            else {  // if top is not the desired cart, impossible to do arrangement
                printf("Impossible\n");
                possible = 0;
                break;
            }
        }
    }
    if (possible){ // if possible, print operations
        i = 0;
        while (printStr[i] != '\0'){
            printf("%c", printStr[i]); //print operations
            i++;
        }
        printf("\n");
    }
}

int main() {
    int cases, carts;
    scanf("%d", &cases);    // no of cases?
    for (int i = 0; i < cases; i++){
        Queue* q = createQueue();   // create queue
        char printStr[Max_STR] = "";    // char array for operations
        scanf("%d", &carts);
        int cartSeq[carts];
        for (int j = 0; j < carts; j++){
            scanf("%d", &cartSeq[j]);
        }
        arrangeCart(q, carts, cartSeq, printStr);
        getchar(); // remove \n
        emptyQueue(q);  // clear queue
    }
    return 0;
}

/**
 * In this PA i used strncat, which exceed the time limit of 1s. 
 * Problem to be considered when using strncat.
 */