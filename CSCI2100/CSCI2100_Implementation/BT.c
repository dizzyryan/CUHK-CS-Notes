#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct _node {
    int data;
    struct _node* left;
    struct _node* right;
} Node;

Node* createNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void insert(Node** root, int data) {
    Node* n = createNode(data);
    if (*root == NULL) {
        *root = n;
        return;
    }
    // if (data == (*root)->data)
    //     return;

    // Level order traversal -> insertion
    Node* temp;
    Node* queue[MAX_SIZE];
    int front = -1, rear = -1;
    queue[++rear] = *root;

    while (front != rear) {
        temp = queue[++front];
        if (temp->left == NULL) {
            temp->left = n;
            return;
        }
        else {
            queue[++rear] = temp->left;
        }
        if (temp->right == NULL) {
            temp->right = n;
            return;
        }
        else {
            queue[++rear] = temp->right;
        }
    }
}

Node* getDeepestRightmostNode(Node* root) {
    Node* temp;
    Node* queue[MAX_SIZE];
    int front = -1, rear = -1;
    queue[++rear] = root;
    while (front != rear) {
        temp = queue[++front];
        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }
        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }
    return temp;
}

void deleteDRN(Node* root, Node* dNode) {
    Node* temp;
    Node* queue[MAX_SIZE];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];
        if (temp == dNode) {
            temp = NULL;
            free(dNode);
            return;
        }
        if (temp->right != NULL) {
            if (temp->right == dNode) {
                temp->right = NULL;
                free(dNode);
                return;
            }
            else {
                queue[++rear] = temp->right;
            }
        }

        if (temp->left != NULL) {
            if (temp->left == dNode) {
                temp->left = NULL;
                free(dNode);
                return;
            }
            else {
                queue[++rear] = temp->left;
            }
        }
    }
}

void deleteNode (Node** root, int data) {
    if (*root == NULL) {
        puts("Empty Tree");
        return;
    }

    if ((*root)->left == NULL && (*root)->right == NULL) {
        if ((*root)->data == data) {
            free(*root);
            *root = NULL;
            return;
        }
        else {
            return;
        }
    }

    Node* temp;
    Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = *root;
    Node* keyNode = NULL;

    while (front != rear) {
        temp = queue[++front];
        if (temp->data == data) {
            keyNode = temp;
        }
        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }
        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }

    if (keyNode != NULL) {
        Node* deepestNode = getDeepestRightmostNode(*root);
        keyNode->data = deepestNode->data;
        deleteDRN(*root, deepestNode);
    }
    else {
        puts("Node not found.");
    }
}

int search(Node* root, int data) {
    if (root == NULL) {
        puts("Empty Tree");
        return -1;
    }

    Node* temp;
    Node* queue[MAX_SIZE];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];
        if (temp->data == data) {
            return 1;
        }
        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }
        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }
    return 0;
}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d -> ", root->data);
    inorder(root->right);
}

void preorder(Node* root) {
  if (root == NULL) {
    return;
  }
  printf("%d-> ", root->data);
  preorder(root->left);
  preorder(root->right);
}

void postorder(Node* root) {
  if (root == NULL) {
    return;
  }
  postorder(root->left);
  postorder(root->right);
  printf("%d-> ", root->data);
}

void freeTree(Node* root) {
	if (!root)
        return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int main() {
    Node* root = NULL;
    search(root, 1);
    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
    insert(&root, 4);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 7);
    search(root, 1);
    deleteNode(&root, 3);
    printf("Inorder: ");
    inorder(root);
    printf("\n");
    printf("Preorder: ");
    preorder(root);
    printf("\n");
    printf("Postorder: ");
    postorder(root);
    printf("\n");
    freeTree(root);
    return 0;
}
