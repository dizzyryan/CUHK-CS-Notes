#include <stdio.h>
#include <stdlib.h>
#define Max_NODE 10010

// tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// create a new node
TreeNode* createNode(int data)
{
    TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insertion for binary tree, check for insert/next
void insert(TreeNode** root, int data) {
    // node to insert
    TreeNode* newNode = createNode(data);

    // empty tree
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    // use queue to check for insertion / balance
    TreeNode* queue[Max_NODE];
    int front = 0, rear = 0;
    // inqueue
    queue[rear++] = *root;

    while (front < rear) {
        // start checking from front
        TreeNode* current = queue[front++];
        
        if (current->left == NULL) {
            // insertion
            current->left = newNode;
            break;
        } else {
            // inqueue
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            // insertion
            current->right = newNode;
            break;
        } else {
            // inqueue
            queue[rear++] = current->right;
        }
    }
}

// static variable to check for print space
// change once only
static int firstDigit = 0;

// print inorder sequence
void inorder(TreeNode* root) {
    if (root == NULL) 
        return;
    // avoid printing 0 (no node)
    else if (root->data == 0) {
        return;
    }
    else {
        // traverse to leftmost
        inorder(root->left);
        if (!firstDigit){
            printf(" ");
        }
        else
            firstDigit = 0;
        printf("%d", root->data);
        // traverse to rightmost
        inorder(root->right);
    }
}

int main() {
    int n, i, j, nodes, temp;
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        // print space condition
        firstDigit++;
        scanf("%d", &nodes);
        // tree pointer to be mapped
        TreeNode* treePtr = NULL;
        for (j = 0; j < nodes; j++){
            scanf("%d", &temp);
            insert(&treePtr, temp);
        }
        inorder(treePtr);
        printf("\n");
        free(treePtr);
    }
    return 0;
}