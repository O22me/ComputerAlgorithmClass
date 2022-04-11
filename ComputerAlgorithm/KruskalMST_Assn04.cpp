/*************************************************************
* NOTE	|	KruskalMST_Assn04.c
* Author	|	�輼��
* Since	|	2022.04.11
**************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 6
#define INF 1000

typedef struct
{
	int weight;	//������ ����ġ
	int u;			//���� 1
	int v;			//���� 2
}SEdge;

int g_arrParent[MAX_VERTICES];	//�θ���
int g_nEdge = 0;

void initializeArrParent(int index)
{
	g_arrParent[index] = -1;
}

int main(void)
{
	int mst; //MST���
	int graph[MAX_VERTICES][MAX_VERTICES] = {
		{ 0, 8, INF, 2, 4, INF },
		{ 8, 0, 1, 4, INF, 2 },
		{ INF, 1, 0, INF, INF, 1 },
		{ 2, 4, INF, 0, 3, 7 },
		{ 4, INF, INF, 3, 0, 9 },
		{ INF, 2, 1, 7, 9, 0 } };
	SEdge arrEdgeSortSet[INF];	//�����迭

	for (int i = 0; i < MAX_VERTICES; i++)
	{
		for (int j = i; j < MAX_VERTICES; j++)
		{
			if (graph[i][j] != INF && graph[i][j] != 0)
			{
				
			}
		}
	}
}