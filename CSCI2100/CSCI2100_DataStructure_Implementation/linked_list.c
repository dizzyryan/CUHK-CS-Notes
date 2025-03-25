#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* next;
} Node;

Node* createNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void insertAtFirst(Node** head, int data) {
    Node* n = createNode(data);
    n->next = *head;
    *head = n;
}

void insertAtEnd(Node** head, int data) {
    Node* n = createNode(data);
    if (*head == NULL) {
        *head = n;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = n;
}

void insertAtPosition(Node** head, int data, int position) {
    Node* n = createNode(data);
    if (position == 0) {
        insertAtFirst(head,data);
        free(n);
        return;
    }
    Node* temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        puts("Position out of range.");
        free(n);
        return;
    }
    n->next = temp->next;
    temp->next = n;
}

void deleteFirst(Node** head) {
    if (*head == NULL) {
        puts("List is empty.");
        return;
    }
    Node* temp = *head;
    *head = temp->next;
    free(temp);
}

void deleteLast(Node** head) {
    if (*head == NULL) {
        puts("List is empty.");
        return;
    }
    Node* temp = *head;
    if (temp->next == NULL) {
        free(temp);
        *head = NULL;
        return;
    }
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void deleteAtPosition(Node** head, int position) {
    if (*head == NULL) {
        puts("List is empty.");
        return;
    }
    Node* temp = *head;
    if (position == 0) {
        deleteFirst(head);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        puts("Position out of range.");
        return;
    }
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

void print(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node** head) {
    Node* temp;
    while (*head) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Driver Code
int main() {
    Node* head = NULL;
    deleteAtPosition(&head, 0);
    deleteFirst(&head);
    deleteFirst(&head);
    insertAtPosition(&head, 0, 5);
    insertAtFirst(&head, 10);
    print(head); 
    insertAtEnd(&head, 20);
    print(head); 
    insertAtEnd(&head, 5);
    print(head); 
    insertAtEnd(&head, 30);
    print(head); 
    insertAtPosition(&head, 15, 2);
    print(head);
    deleteFirst(&head);
    print(head); 
    deleteLast(&head);
    print(head); 
    deleteAtPosition(&head, 1);
    print(head); 
    freeList(&head);
    return 0;
}
