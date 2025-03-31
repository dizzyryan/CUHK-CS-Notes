#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	int height;
	struct _node* left;
	struct _node* right;
} AVLNode;

int height(AVLNode* n) {
	if (!n)
		return 0;
	return n->height;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void updateHeight(AVLNode* tree) {
	tree->height = max(height(tree->left), height(tree->right)) + 1;
}

AVLNode* createNode(int data) {
	AVLNode* n = (AVLNode*)malloc(sizeof(AVLNode));
	n->data = data;
	n->height = 1;
	n->left = NULL;
	n->right = NULL;
	return n;
}

AVLNode* leftRotation(AVLNode* x) {
	AVLNode* y = x->right;
	x->right = y->left;
	y->left = x;
	updateHeight(x);
	updateHeight(y);
	return y;
}

AVLNode* rightRotation(AVLNode* x) {
	AVLNode* y = x->left;
	x->left = y->right;
	y->right = x;
	updateHeight(x);
	updateHeight(y);
	return y;
}

AVLNode* LRRotation(AVLNode* x) {
	x->left = leftRotation(x->left);
	return rightRotation(x);
}

AVLNode* RLRotation(AVLNode* x) {
	x->right = rightRotation(x->right);
	return leftRotation(x);
}

AVLNode* balance(AVLNode* tree) {
	if (!tree)
		return tree;
	int balance = height(tree->left) - height(tree->right);
	if (balance > 1) {
		if (height(tree->left->left) >= height(tree->left->right)) {
			tree = rightRotation(tree);
		}
		else {
			tree = LRRotation(tree);
		}
	}
	else if (balance < -1) {
		if (height(tree->right->right) >= height(tree->right->left)) {
			tree = leftRotation(tree);
		}
		else {
			tree = RLRotation(tree);
		}
	}
	return tree;
}

AVLNode* insert(AVLNode* tree, int data) {
	if (!tree) {
		return createNode(data);
	}
	else if (data < tree->data) {
		tree->left = insert(tree->left, data);
	}
	else if (data > tree->data)	{
		tree->right = insert(tree->right, data);
	}
	updateHeight(tree);
	return balance(tree);
}

int getMin(AVLNode* tree) {
	if (!tree)
		return -1;

	if (!(tree->left))
		return tree->data;

	return getMin(tree->left);
}

AVLNode* delete(AVLNode* tree, int data) {
	if (!tree)
		return tree;
	if (data < tree->data) {
		tree->left = delete(tree->left, data);
	}
	else if (data > tree->data) {
		tree->right = delete(tree->right, data);
	}
	else {
		if (tree->right && tree->left) {
			tree->data = getMin(tree->right);
			tree->right = delete(tree->right, tree->data);
		} else {
			AVLNode* temp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(temp);
		}
	}
	return balance(tree);
}

AVLNode* search(AVLNode* root, int tar) {
    if (root != NULL) {
        if (tar < root->data) {
            return search(root->left, tar);
        }
        if (tar > root->data) {
            return search(root->right, tar);
        }
        else
            return root;
    }
    else
        return NULL;
}

void inorder(AVLNode* root) {
	if (root == NULL) {
		return;
	}
	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

void preorder(AVLNode* root) {
	if (root == NULL) {
		return;
	}
	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

void postorder(AVLNode* root) {
	if (root == NULL) {
		return;
	}
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->data);
}

void freeTree(AVLNode* node) {
	if (!node)
		return;
	freeTree(node->left);
	freeTree(node->right);
	free(node);
}

void printAll(AVLNode* tree) {
	printf("Inorder: "); inorder(tree); putchar('\n');
	printf("Preorder: "); preorder(tree); putchar('\n');
	printf("Postorder: "); postorder(tree); putchar('\n');
}

int main() {
	AVLNode* tree = NULL;
	tree = insert(tree, 22);
	tree = insert(tree, 1);
	tree = insert(tree, 14);
	tree = insert(tree, 19);
	tree = insert(tree, 3);
	tree = insert(tree, 27);
	printf(search(tree, 22) ? "Yes1\n" : "No");
	printf(search(tree, 1) ? "Yes2\n" : "No");
	printf(search(tree, 22) ? "Yes3\n" : "No");
	printf(search(tree, 23) ? "No" : "Yes4\n");
	printAll(tree);
	tree = delete(tree, 14);
	tree = delete(tree, 3);
	tree = delete(tree, 27);
	printAll(tree);
	tree = insert(tree, 3);
	tree = insert(tree, 27);
	printAll(tree);
	freeTree(tree);
	return 0;
}
