#include <stdio.h>
#include <stdlib.h>

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

Node* insert(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    }
    else if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

int getMin(Node* root) {
	if (!root) {
        puts("Empty Tree.");
		return -1;
    }
	if (!(root->left))
		return root->data;
	return getMin(root->left);
}

Node* search(Node* root, int tar)
{
    if (root != NULL){
        if (tar < root->data){
            return search(root->left, tar);
        }
        if (tar > root->data){
            return search(root->right, tar);
        }
        else
            return root;
    }
    else
        return NULL;
}

Node* delete(Node* root, int tar) {
    Node* temp; 
    if (root == NULL)
        return root;
    if (tar < root->data) {
        root->left = delete(root->left, tar);
    }
    else if (tar > root->data) {
        root->right = delete(root->right, tar);
    }
    else {
        if (root->left != NULL && root->right != NULL) {
            root->data = getMin(root->right);
            root->right = delete(root->right, root->data);
        } 
        else {
            temp = root;
            if (root->left != NULL) {
                root = root->left;
            }
            else if (root->right != NULL) {
                root = root->right;
            }
            else 
                root = NULL;
            free(temp);
        }
    }
    return root;
}

int height(Node* root) {
    if (!root){
        return -1;
    }
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight > rightHeight) {
            return ++leftHeight;
        }
        else
            return ++rightHeight;
    }
}

void inorder(Node* root)
{
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d -> ", root->data);
    inorder(root->right);
}

void preorder(Node* root){
  if (root == NULL){
    return;
  }
  printf("%d -> ", root->data);
  preorder(root->left);
  preorder(root->right);
}

void postorder(Node* root){
  if (root == NULL){
    return;
  }
  postorder(root->left);
  postorder(root->right);
  printf("%d -> ", root->data);
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
    root = insert(root, 14);
    root = insert(root, 1);
    root = insert(root, 22);
    root = insert(root, 3);
    root = insert(root, 19);
    root = insert(root, 27);
    root = insert(root, 26);
    postorder(search(root, 22)); putchar('\n');
    postorder(root); putchar('\n');
    printf(search(root, 19) != NULL ? "Found\n" : "Not Found\n");
    printf(search(root, 80) != NULL ? "Found\n" : "Not Found\n");
    root = delete(root, 22);
    preorder(root); putchar('\n');
    inorder(root); putchar('\n');
    postorder(root); putchar('\n');
    freeTree(root);
    return 0;
}