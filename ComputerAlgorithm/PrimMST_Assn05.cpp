#include <stdio.h>

#define MAX_VERTICES 6
#define INF 1000

bool selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertice(int graph[][MAX_VERTICES], int n_vertices)
{
	int v;

	for (int i = 0; i < n_vertices; i++)
	{
		if (!selected[i])
		{
			v = i;
			break;
		}
	}

	for (int i = 0; i < n_vertices; i++)
	{
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	}
	return v;
}

void prim(int graph[][MAX_VERTICES], int start_vertex, int n_vertices)
{
	int u, v;	//두 정점 선언

	//정점 초기화
	for (u = 0; u < n_vertices; u++) distance[u] = INF;

	for (int i = 0; i < n_vertices; i++)
	{
		u = get_min_vertice(graph, n_vertices);
		selected[u] = true;

		if (distance[u] == INF) return;

		printf("Selected Vertice : %d", u);

		for (v = 0; v < n_vertices; v++)
		{
			if (graph[u][v] != INF)
			{
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