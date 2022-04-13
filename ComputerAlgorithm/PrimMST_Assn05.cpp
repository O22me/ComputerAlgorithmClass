#include <stdio.h>

#define MAX_VERTICES 6
#define INF 1000

bool selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertice(int graph[][MAX_VERTICES], int n_vertices)
{
	int v;

	//선택되지 않았던 정점 찾기
	for (int i = 0; i < n_vertices; i++)
	{
		if (!selected[i])
		{
			v = i;
			break;
		}
	}

	//모든 정점에 대해
	for (int i = 0; i < n_vertices; i++)
	{
		//선택되지 않았고 최소 가중치를 갖는 정점 선택
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	}
	return v;
}

void prim(int graph[][MAX_VERTICES], int start_vertex, int n_vertices)
{
	int u, v;	//두 정점 선언

	//정점 초기화
	for (u = 0; u < n_vertices; u++) distance[u] = INF;
	distance[start_vertex] = 0;	//첫 정점 0으로 초기화

	//핵심 코드
	for (int i = 0; i < n_vertices; i++)
	{
		//가장 가중치가 낮은 간선을 가진 정점을 반환
		u = get_min_vertice(graph, n_vertices);
		selected[u] = true;

		//추가된 코드 : 완전 그래프가 아닌 나눠진 그래프인 경우 종료.
		if (distance[u] == INF) return;

		printf("Selected Vertice : %d\n", u);

		//그래프의 가중치 업데이트
		for (v = 0; v < n_vertices; v++)
		{
			//현재 연장된 정점에서 연결가능한 정점 중..
			if (graph[u][v] != INF)
			{
				//간선의 가중치에 따른 distance 배열 업데이트
				if (!selected[v] && graph[u][v] < distance[v]) distance[v] = graph[u][v];
			}
		}
	}
}

int main(void)
{
	int primMST = 0;
	int graph[MAX_VERTICES][MAX_VERTICES] = {
		{ 0, 8, INF, 2, 4, INF },
		{ 8, 0, 1, 4, INF, 2 },
		{ INF, 1, 0, INF, INF, 1 },
		{ 2, 4, INF, 0, 3, 7 },
		{ 4, INF, INF, 3, 0, 9 },
		{ INF, 2, 1, 7, 9, 0 } };

	prim(graph, 0, MAX_VERTICES);

	return 0;
}