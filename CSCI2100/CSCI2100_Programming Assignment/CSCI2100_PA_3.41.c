#include <stdio.h>
#include <stdlib.h>

// store no. of rotations for output
int rotations = 0;

// tree node
typedef struct AVLNode {
	int data;
	int height;
	struct AVLNode *left;
	struct AVLNode *right;
} AVLNode;

// height of a node
int height(AVLNode *n) {
	if (n != NULL) {
		return n->height;
	}
	else {
		return 0; // Empty tree
	}
}

// create a new node
AVLNode *createNode(int data) {
	AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
	newNode->data = data;
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// find max among two values
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

// left rotation
AVLNode *leftRotation(AVLNode *x) {
	// Swap pointers
	AVLNode *y = x->right;
	x->right = y->left;
	y->left = x;
	rotations++;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(x->height, height(y->right)) + 1;
	return y;
}

// right rotation
AVLNode *rightRotation(AVLNode *x) {
	// Swap pointers
	AVLNode *y = x->left;
	x->left = y->right;
	y->right = x;
	rotations++;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), x->height) + 1;
	return y;
}

// left-right rotation
AVLNode *LRRotation(AVLNode *x) {
	x->left = leftRotation(x->left); // left rotation of left child
	return rightRotation(x);		 // right rotation
}

// right-left rotation
AVLNode *RLRotation(AVLNode *x) {
	x->right = rightRotation(x->right); // right rotation of right child
	return leftRotation(x);				// left rotation
}

// node insertion
AVLNode *insert(int data, AVLNode *tree) {
	// node to insert
	if (tree == NULL) {
		tree = createNode(data);
	}
	// check for left insertion
	else if (data < tree->data) {
		tree->left = insert(data, tree->left);
		if (height(tree->left) - height(tree->right) == 2) {
			if (data < tree->left->data) { // right rotation
				tree = rightRotation(tree);
			}
			else { //  left-right rotation
				tree = LRRotation(tree);
			}
		}
	}
	// check for right insertion
	else if (data > tree->data)	{
		tree->right = insert(data, tree->right);
		if (height(tree->right) - height(tree->left) == 2) {
			if (data > tree->right->data) { // left rotation
				tree = leftRotation(tree);
			}
			else { // right-left rotation
				tree = RLRotation(tree);
			}
		}
	}
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

// free memory
void freeTree(AVLNode *node) {
	if (node == NULL)
		return;
	freeTree(node->left);
	freeTree(node->right);
	free(node);
}

int main() {
	int n, i, j, nodes, temp;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		rotations = 0;
		scanf("%d", &nodes);
		// AVL tree pointer to be mapped
		AVLNode *treePtr = NULL;
		for (j = 0; j < nodes; j++) {
			scanf("%d", &temp);
			treePtr = insert(temp, treePtr);
		}
		printf("%d\n", rotations);
		freeTree(treePtr);
	}
	return 0;
}
