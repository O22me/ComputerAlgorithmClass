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

//KruskalMST를 위한 define
#define MAX_VERTICES 6
#define INF 1000

typedef struct
{
	int weight;	//간선의 가중치
	int u;			//정점 1
	int v;			//정점 2
}SEdge;

//전역변수 선언 부분
int g_arrParent[MAX_VERTICES];	//부모노드
int g_nEdge = 0;						//간선의 개수

//힙정렬을 위한 코드
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
	//최초 힙 구성
	for (int i = 1; i < n; i++)
	{
		now = i;
		//now가 0이 아니면 힙의 루트가 아님.
		while (now > 0)
		{
			parent = PARENT(now);
			if (arrEdgeSet[now].weight > arrEdgeSet[parent].weight)	//가중치가 부모보다 크면
			{
				swapEdge(&arrEdgeSet[now], &arrEdgeSet[parent]);		//부모와 교환
				now = parent;	//인덱스 부모로 설정
			}
			else break;	//정확한 자리
		}
	}
}

//now와 왼쪽, 오른쪽 자식 중에 가중치가 가장 큰 인덱스 반환
int findMaxIndex(SEdge arrEdgeSet[], int n, int now)
{
	int leftChild = LEFT_CHILD(now);
	int rightChild = RIGHT_CHILD(now);

	//오른쪽 자식이 없을경우 왼쪽자식과 now를 비교
	if (rightChild >= n)
	{
		if (arrEdgeSet[now].weight < arrEdgeSet[leftChild].weight) return leftChild;
		else return now;
	}
	//그 외의 경우 왼쪽과 오른쪽 자식을 비교후 큰 가중치 값 인덱스 반환
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

	//왼쪽 자식이 있다면
	while (LEFT_CHILD(now) < n)
	{
		heavyWeightIndex = findMaxIndex(arrEdgeSet, n, now); //큰 가중치 인덱스 반환
		if (heavyWeightIndex == now) break;	//정확한 자리
		swapEdge(&arrEdgeSet[heavyWeightIndex], &arrEdgeSet[now]); //now와 큰 가중치 자리 교환
		now = heavyWeightIndex;	//큰 가중치 값의 위치를 now로 설정
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

//KruskalMST를 위한 코드
void initializeArrParent(int index)
{
	g_arrParent[index] = -1;
}

//정점 v가 속하는 트리의 루트 노드 반환
int findSet(int v)
{
	//루트 노드까지 반복
	while (g_arrParent[v] >= 0)
	{
		v = g_arrParent[v];
	}
	return v; 
}

//두 정점을 합침.
void union_set(int u, int v)
{
	int temp;
	
	//두 정점 모두 루트노드일경우
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
	//한 정점만 루트 노드인경우(u가 루트노드)
	else if (g_arrParent[u] < 0 && g_arrParent[v] >= 0)
	{
		temp = g_arrParent[u];
		g_arrParent[u] = g_arrParent[v];
		g_arrParent[g_arrParent[v]] += temp;
	}
	//한 정점만 루트 노드인경우(v가 루트노드)
	else if (g_arrParent[u] >= 0 && g_arrParent[v] < 0)
	{
		temp = g_arrParent[v];
		g_arrParent[v] = g_arrParent[u];
		g_arrParent[g_arrParent[u]] += temp;
	}
	//두 정점 모두 루트 노드가 아닐때
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
	int mst_e = 0;		//최소 비용
	int mst_e_n = 0;	//최소 비용을 구하는데 선택된 간선의 수

	heapSortEdge(arrEdgeSet, g_nEdge);	//간선 가중치 정렬

	for (i = 0; i < nVertices; i++)
	{
		initializeArrParent(i);
	}
	for (i = 0; mst_e_n < nVertices - 1; i++)
	{
		u = arrEdgeSet[i].u;
		v = arrEdgeSet[i].v;
		if (findSet(u) != findSet(v))	//같은 집합 안에 없을경우 Cycle아님
		{
			mst_e += arrEdgeSet[i].weight;
			mst_e_n++;
			union_set(u, v);
		}
		else printf("%d, %d is cycle.\n", u, v);	//그 외는 모두 사이클
	}
	return mst_e;
}

int main(void)
{
	int mst = 0; //MST비용
	//그래프를 배열을 통해 가중치 표현
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
				//그래프에서의 가중치 배열 작성
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