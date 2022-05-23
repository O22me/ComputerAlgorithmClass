#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define ALPH_NUM 26

//힙정렬을 위한 define
#define LEFT_CHILD(x) (2*x+1)
#define RIGHT_CHILD(x) (2*x+2)
#define PARENT(x) ((x-1)/2)

typedef struct Node
{
	char alphabet;
	int frequency;
	struct Node* left;
	struct Node* right;
}Node;

void swapNode(Node* x, Node* y)
{
	Node temp = *x;
	*x = *y;
	*y = temp;
}

Node* makeNode(char alphabet, int frequency)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (newnode == NULL) {	//malloc함수간 오류 발생시 NULL반환.
		free(newnode);
		return NULL;
	}
	newnode->alphabet = alphabet;
	newnode->frequency = frequency;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

int main(void)
{
	Node* root;

	return 0;
}