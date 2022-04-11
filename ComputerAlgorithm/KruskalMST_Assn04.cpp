/*************************************************************
* NOTE	|	KruskalMST_Assn04.c
* Author	|	�輼��
* Since	|	2022.04.11
**************************************************************/

#include <stdio.h>
#include <stdlib.h>

//�������� ���� define
#define LEFT_CHILD(x) (2*x+1)
#define RIGHT_CHILD(x) (2*x+2)
#define PARENT(x) ((x-1)/2)

//KruskalMST�� ���� define
#define MAX_VERTICES 6
#define INF 1000

typedef struct
{
	int weight;	//������ ����ġ
	int u;			//���� 1
	int v;			//���� 2
}SEdge;

//�������� ���� �κ�
int g_arrParent[MAX_VERTICES];	//�θ���
int g_nEdge = 0;						//������ ����

//�������� ���� �ڵ�
void swapEdge(SEdge *x, SEdge *y)
{
	SEdge temp = *x;
	*x = *y;
	*y = temp;
}

void initializeHeapEdge(SEdge arrEdgeSet[], int n)
{
	int parent = 0;
	int now;
	//���� �� ����
	for (int i = 1; i < n; i++)
	{
		now = i;
		//now�� 0�� �ƴϸ� ���� ��Ʈ�� �ƴ�.
		while (now > 0)
		{
			parent = PARENT(now);
			if (arrEdgeSet[now].weight > arrEdgeSet[parent].weight)	//����ġ�� �θ𺸴� ũ��
			{
				swapEdge(&arrEdgeSet[now], &arrEdgeSet[parent]);		//�θ�� ��ȯ
				now = parent;	//�ε��� �θ�� ����
			}
			else break;	//��Ȯ�� �ڸ�
		}
	}
}

//now�� ����, ������ �ڽ� �߿� ����ġ�� ���� ū �ε��� ��ȯ
int findMaxIndex(SEdge arrEdgeSet[], int n, int now)
{
	int leftChild = LEFT_CHILD(now);
	int rightChild = RIGHT_CHILD(now);

	//������ �ڽ��� ������� �����ڽİ� now�� ��
	if (rightChild >= n)
	{
		if (arrEdgeSet[now].weight < arrEdgeSet[leftChild].weight) return leftChild;
		else return now;
	}
	//�� ���� ��� ���ʰ� ������ �ڽ��� ���� ū ����ġ �� �ε��� ��ȯ
	if (arrEdgeSet[leftChild].weight < arrEdgeSet[rightChild].weight)
	{
		return rightChild;
	}
	return leftChild;
}

void makeHeapEdge(SEdge arrEdgeSet[], int n)
{
	int now = 0;
	int heavyWeightIndex = 0;

	//���� �ڽ��� �ִٸ�
	while (LEFT_CHILD(now) < n)
	{
		heavyWeightIndex = findMaxIndex(arrEdgeSet, n, now); //ū ����ġ �ε��� ��ȯ
		if (heavyWeightIndex == now) break;	//��Ȯ�� �ڸ�
		swapEdge(&arrEdgeSet[heavyWeightIndex], &arrEdgeSet[now]); //now�� ū ����ġ �ڸ� ��ȯ
		now = heavyWeightIndex;	//ū ����ġ ���� ��ġ�� now�� ����
	}
}

void heapSortEdge(SEdge arrEdgeSet[], int n)
{
	initializeHeapEdge(arrEdgeSet, n);
	n--;
	swapEdge(&arrEdgeSet[0], &arrEdgeSet[n]);

	while (n > 1)
	{
		makeHeapEdge(arrEdgeSet, n);
		n--;
		swapEdge(&arrEdgeSet[0], &arrEdgeSet[n]);
	}
}

//KruskalMST�� ���� �ڵ�
void initializeArrParent(int index)
{
	g_arrParent[index] = -1;
}

//���� v�� ���ϴ� Ʈ���� ��Ʈ ��� ��ȯ
int findSet(int v)
{
	//��Ʈ ������ �ݺ�
	while (g_arrParent[v] >= 0)
	{
		v = g_arrParent[v];
	}
	return v; 
}

//�� ������ ��ħ.
void union_set(int u, int v)
{
	int temp;
	
	//�� ���� ��� ��Ʈ����ϰ��
	if (g_arrParent[u] < 0 && g_arrParent[v] < 0)
	{
		if (g_arrParent[u] <= g_arrParent[v])
		{
			temp = g_arrParent[v];
			g_arrParent[v] = u;
			g_arrParent[u] += temp;
		}
		else
		{
			temp = g_arrParent[u];
			g_arrParent[u] = v;
			g_arrParent[v] += temp;
		}
	}
	//�� ������ ��Ʈ ����ΰ��(u�� ��Ʈ���)
	else if (g_arrParent[u] < 0 && g_arrParent[v] >= 0)
	{
		temp = g_arrParent[u];
		g_arrParent[u] = g_arrParent[v];
		g_arrParent[g_arrParent[v]] += temp;
	}
	//�� ������ ��Ʈ ����ΰ��(v�� ��Ʈ���)
	else if (g_arrParent[u] >= 0 && g_arrParent[v] < 0)
	{
		temp = g_arrParent[v];
		g_arrParent[v] = g_arrParent[u];
		g_arrParent[g_arrParent[u]] += temp;
	}
	//�� ���� ��� ��Ʈ ��尡 �ƴҶ�
	else
	{
		temp = g_arrParent[u];
		g_arrParent[u] = g_arrParent[v];
		g_arrParent[temp] = g_arrParent[v];
	}
	printf("%d and %d is selected.\n", u, v);
}

int kruskal(SEdge arrEdgeSet[], int nVertices)
{
	int i, u, v;
	int mst_e = 0;		//�ּ� ���
	int mst_e_n = 0;	//�ּ� ����� ���ϴµ� ���õ� ������ ��

	heapSortEdge(arrEdgeSet, g_nEdge);	//���� ����ġ ����

	for (i = 0; i < nVertices; i++)
	{
		initializeArrParent(i);
	}
	for (i = 0; mst_e_n < nVertices - 1; i++)
	{
		u = arrEdgeSet[i].u;
		v = arrEdgeSet[i].v;
		if (findSet(u) != findSet(v))	//���� ���� �ȿ� ������� Cycle�ƴ�
		{
			mst_e += arrEdgeSet[i].weight;
			mst_e_n++;
			union_set(u, v);
		}
		else printf("%d, %d is cycle.\n", u, v);	//�� �ܴ� ��� ����Ŭ
	}
	return mst_e;
}

int main(void)
{
	int mst = 0; //MST���
	//�׷����� �迭�� ���� ����ġ ǥ��
	int graph[MAX_VERTICES][MAX_VERTICES] = {
		{ 0, 8, INF, 2, 4, INF },
		{ 8, 0, 1, 4, INF, 2 },
		{ INF, 1, 0, INF, INF, 1 },
		{ 2, 4, INF, 0, 3, 7 },
		{ 4, INF, INF, 3, 0, 9 },
		{ INF, 2, 1, 7, 9, 0 } };
	SEdge arrEdgeSet[INF];	//�����迭

	for (int i = 0; i < MAX_VERTICES; i++)
	{
		for (int j = i; j < MAX_VERTICES; j++)
		{
			if (graph[i][j] != INF && graph[i][j] != 0)
			{
				//�׷��������� ����ġ �迭 �ۼ�
				arrEdgeSet[g_nEdge].weight = graph[i][j];
				arrEdgeSet[g_nEdge].u = i;
				arrEdgeSet[g_nEdge].v = j;
				g_nEdge++;
			}
		}
	}
	mst = kruskal(arrEdgeSet, MAX_VERTICES);
	printf("KruskalMST = %d", mst);

	return 0;
}