#include <stdio.h>
#include <stdlib.h>

// tree node
typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

// create a new node
TreeNode *createNode(int data) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// insertion for binary tree, check for insert/next
TreeNode *insert(int preorder[], int postorder[], int lo, int hi, int *preindex, int size) {
	if (lo > hi || *preindex >= size) {
		return NULL;
	}
	TreeNode *root = createNode(preorder[*preindex]);
	(*preindex)++;

	// if it has 1 element only, return immediately
	if (lo == hi) {
		return root;
	}

	// search for next element
	int i;
	for (i = lo; i <= hi; ++i) {
		if (preorder[*preindex] == postorder[i])
			break;
	}

	// recursively check
	if (i <= hi) {
		root->left = insert(preorder, postorder, lo, i, preindex, size);
		root->right = insert(preorder, postorder, i + 1, hi - 1, preindex, size);
	}
	return root;
}

// static variable to check for print space
// change once only
static int firstDigit = 0;

// print inorder sequence
void inorder(TreeNode *root) {
	if (root == NULL)
		return;
	// avoid printing 0 (no node)
	else if (root->data == 0) {
		return;
	}
	else {
		// traverse to leftmost
		inorder(root->left);
		if (!firstDigit) {
			printf(" ");
		}
		else
			firstDigit = 0;
		printf("%d", root->data);
		// traverse to rightmost
		inorder(root->right);
	}
}

// free memory
void freeTree(TreeNode *root) {
	if (root == NULL)
		return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int main() {
	int n, i, j, nodes, temp;
	int lo, hi, preindex;
	scanf("%d", &n);
	for (i = 0; i < n; i++)	{
		scanf("%d", &nodes);
		// tree pointer to be mapped (allocating space)
		int *preorder = (int *)malloc(sizeof(int) * (nodes + 5));
		int *postorder = (int *)malloc(sizeof(int) * (nodes + 5));
		TreeNode *treePtr = NULL;
		// preorder
		for (j = 0; j < nodes; j++)	{
			scanf("%d", &temp);
			preorder[j] = temp;
		}
		// postorder
		for (j = 0; j < nodes; j++)	{
			scanf("%d", &temp);
			postorder[j] = temp;
		}
		firstDigit = 1;
		lo = 0;
		hi = nodes - 1;
		preindex = 0;
		treePtr = insert(preorder, postorder, lo, hi, &preindex, nodes);
		// print order
		inorder(treePtr);
		printf("\n");
		// free memory
		freeTree(treePtr);
		free(preorder);
		free(postorder);
	}
	return 0;
}