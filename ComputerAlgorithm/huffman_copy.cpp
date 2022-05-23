#include <stdio.h> 
#include <queue> 
#include <functional> 
#include <stdlib.h> 
using namespace std; 
typedef struct Node 
{ 
	char c; //0이면 그룹 
	int fre; //빈도수 
	Node* left; 
	Node* right; 
	bool operator > (const Node A) const { 
		return fre > A.fre;
	} 
} Node, *PNode;

int N;
priority_queue<Node, vector<Node>, greater<Node> > heap;
char code[100];

void print_code(PNode node, int size)
{ 
	if (node->c)
	{ 
		code[size] = 0; //문자 발견-> 이진코드 종료문자
		printf("%c :%s\n", node->c, code);
	}
	else
	{ 
		if (node->left)
		{
			code[size] = '0'; //이진 코드 0
		print_code(node->left, size + 1);
		}
		if (node->right)
		{
			code[size] = '1'; //이진 코드 1
			print_code(node->right, size + 1);
		}
	}
}

int main(void) 
{ 
	int i, j;
	char c;
	int fre;
	Node node = {'0',0,0,0};
	PNode parent, left, right;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("\n%c %d", node.c, node.fre);
		heap.push(node);
	}
	for (int i = 1; i < N; i++)
	{
		left = (PNode)malloc(sizeof(Node));
		right = (PNode)malloc(sizeof(Node));
		parent = (PNode)malloc(sizeof(Node)); // 빈도수가 가장 작은 문자 2개 선택
		*left = heap.top();
		heap.pop();
		*right = heap.top();
		heap.pop(); //새 노드를 생성하여 두 자식 노드로 지정
		parent->left = left;
		parent->right = right; //새 노드의 빈도수 = 자식 노드의 빈도수
		parent->fre = left->fre + right->fre;
		parent->c = 0; // 그룹
		heap.push(*parent); //새 그룹을 힙에 삽입
	}
	print_code(&heap.top(), 0);
	return 0;
}
