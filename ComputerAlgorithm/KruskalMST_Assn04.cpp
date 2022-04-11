/*************************************************************
* NOTE	|	KruskalMST_Assn04.c
* Author	|	김세훈
* Since	|	2022.04.11
**************************************************************/

#include <stdio.h>
#include <stdlib.h>

//힙정렬을 위한 define
#define LEFT_CHILD(x) (2*x+1)
#define RIGHT_CHILD(x) (2*x+2)
#define PARENT(x) ((x-1)/2)

#define MAX_VERTICES 6
#define INF 1000

typedef struct
{
	int weight;	//간선의 가중치
	int u;			//정점 1
	int v;			//정점 2
}SEdge;

int g_arrParent[MAX_VERTICES];	//부모노드
int g_nEdge = 0;

void heapSortEdge(SEdge arrEdgeSet[], int n)
{

}

void initializeArrParent(int index)
{
	g_arrParent[index] = -1;
}

int kruskal(SEdge arrEdgeSet[], int nVertices)
{

}

int main(void)
{
	int mst; //MST비용
	int graph[MAX_VERTICES][MAX_VERTICES] = {
		{ 0, 8, INF, 2, 4, INF },
		{ 8, 0, 1, 4, INF, 2 },
		{ INF, 1, 0, INF, INF, 1 },
		{ 2, 4, INF, 0, 3, 7 },
		{ 4, INF, INF, 3, 0, 9 },
		{ INF, 2, 1, 7, 9, 0 } };
	SEdge arrEdgeSet[INF];	//간선배열

	for (int i = 0; i < MAX_VERTICES; i++)
	{
		for (int j = i; j < MAX_VERTICES; j++)
		{
			if (graph[i][j] != INF && graph[i][j] != 0)
			{
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