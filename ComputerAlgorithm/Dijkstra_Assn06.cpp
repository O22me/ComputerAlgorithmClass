#include <stdio.h>

#define MAX_VERTICES 6
#define INF 1000

bool visited[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertice(int graph[][MAX_VERTICES], int n_vertices)
{
	int v = 0;

	//선택되지 않았던 정점 찾기(v의 초기화)
	for (int i = 0; i < n_vertices; i++)
	{
		if (!visited[i])
		{
			v = i;
			break;
		}
	}

	//모든 정점에 대해
	for (int i = 0; i < n_vertices; i++)
	{
		//방문하지 않았고 최소 가중치를 갖는 정점 선택
		if (!visited[i] && (distance[i] < distance[v])) v = i;
	}
	return v;
}

void dijkstra(int graph[][MAX_VERTICES], int start_vertex, int n_vertices)
{
	int u;
	//start_vertex 기준 간선 가중치(distance) 초기화
	for (int i = 0; i < MAX_VERTICES; i++) distance[i] = graph[start_vertex][i];
	visited[start_vertex] = true;

	for (int i = 0; i < n_vertices; i++)
	{
		//선택되지 않은 가장 가중치가 낮은 간선을 가진 정점을 반환
		u = get_min_vertice(graph, n_vertices);
		visited[u] = true;

		//가장 가중치가 낮은 간선 = INF인 상황
		if (distance[u] == INF) return;

		for (int v = 0; v < n_vertices; v++)
		{
			//방문하지 않은 정점에 대해서
			if (!visited[v])
			{
				//추가된 정점을 포함한 거리와 비교연산을 통해 가중치가 짧은 것을 선택
				if (distance[v] > graph[u][v] + distance[u]) distance[v] = graph[u][v] + distance[u];
			}
		}
	}
}

int main(void)
{
	int graph[MAX_VERTICES][MAX_VERTICES] = {
		{ 0, 8, INF, 2, 4, INF },
		{ 8, 0, 1, 4, INF, 2 },
		{ INF, 1, 0, INF, INF, 1 },
		{ 2, 4, INF, 0, 3, 7 },
		{ 4, INF, INF, 3, 0, 9 },
		{ INF, 2, 1, 7, 9, 0 } 
	};

	dijkstra(graph, 4, MAX_VERTICES);

	for (int i = 0; i < MAX_VERTICES; i++) printf("%d ", distance[i]);

	return 0;
}