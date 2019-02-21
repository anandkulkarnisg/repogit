#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>

using namespace std;

/* A Binary Tree node */
struct TNode
{
	int data;
	struct TNode* left;
	struct TNode* right;
};

struct TNode* newNode(int data);

/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(int arr[], int start, int end)
{
	/* Base Case */
	if (start > end)
		return NULL;

	/* Get the middle element and make it root */
	int mid = (start + end)/2;
	struct TNode *root = newNode(arr[mid]);

	/* Recursively construct the left subtree and make it
	   left child of root */
	root->left =  sortedArrayToBST(arr, start, mid-1);

	/* Recursively construct the right subtree and make it
	   right child of root */
	root->right = sortedArrayToBST(arr, mid+1, end);

	return root;
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct TNode* newNode(int data)
{
	struct TNode* node = (struct TNode*)
		malloc(sizeof(struct TNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}

/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node)
{
	if (node == NULL)
	{
		return;
	}
	printf("%d ", node->data);
	preOrder(node->left);
	preOrder(node->right);
}

void inOrder(struct TNode* node)
{

	// In order traversal is left child -> root -> right child.
	if(node == nullptr)
		return;

	inOrder(node->left);
	printf("%d ", node->data);
	inOrder(node->right);
}

void postOrder(struct TNode* node)
{
	
	if(node == NULL)
		return;

	postOrder(node->left);
	postOrder(node->right);
	printf("%d ",node->data);
}

/* Driver program to test above functions */
int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int n = sizeof(arr)/sizeof(arr[0]);

	/* Convert List to BST */
	struct TNode *root = sortedArrayToBST(arr, 0, n-1);
	printf("n PreOrder Traversal of constructed BST ");
	preOrder(root);
	cout << endl;

	// Print the sorted array using the inOrder traversal.
	inOrder(root);
	cout << endl;
}
