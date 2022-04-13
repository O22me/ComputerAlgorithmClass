#include <stdio.h>

#define MAX_VERTICES 6
#define INF 1000

bool visited[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertice(int graph[][MAX_VERTICES], int n_vertices)
{
	int v = 0;

	//���õ��� �ʾҴ� ���� ã��(v�� �ʱ�ȭ)
	for (int i = 0; i < n_vertices; i++)
	{
		if (!visited[i])
		{
			v = i;
			break;
		}
	}

	//��� ������ ����
	for (int i = 0; i < n_vertices; i++)
	{
		//�湮���� �ʾҰ� �ּ� ����ġ�� ���� ���� ����
		if (!visited[i] && (distance[i] < distance[v])) v = i;
	}
	return v;
}

void dijkstra(int graph[][MAX_VERTICES], int start_vertex, int n_vertices)
{
	int u;
	//start_vertex ���� ���� ����ġ(distance) �ʱ�ȭ
	for (int i = 0; i < MAX_VERTICES; i++) distance[i] = graph[start_vertex][i];
	visited[start_vertex] = true;

	for (int i = 0; i < n_vertices; i++)
	{
		//���õ��� ���� ���� ����ġ�� ���� ������ ���� ������ ��ȯ
		u = get_min_vertice(graph, n_vertices);
		visited[u] = true;

		//���� ����ġ�� ���� ���� = INF�� ��Ȳ
		if (distance[u] == INF) return;

		for (int v = 0; v < n_vertices; v++)
		{
			//�湮���� ���� ������ ���ؼ�
			if (!visited[v])
			{
				//�߰��� ������ ������ �Ÿ��� �񱳿����� ���� ����ġ�� ª�� ���� ����
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