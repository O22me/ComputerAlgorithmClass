#include <stdio.h>

#define MAX_VERTICES 6
#define INF 1000

bool selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertice(int graph[][MAX_VERTICES], int n_vertices)
{
	int v = 0;

	//���õ��� �ʾҴ� ���� ã��
	for (int i = 0; i < n_vertices; i++)
	{
		if (!selected[i])
		{
			v = i;
			break;
		}
	}

	//��� ������ ����
	for (int i = 0; i < n_vertices; i++)
	{
		//���õ��� �ʾҰ� �ּ� ����ġ�� ���� ���� ����
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	}
	return v;
}

void prim(int graph[][MAX_VERTICES], int start_vertex, int n_vertices)
{
	int u, v;	//�� ���� ����

	//���� �ʱ�ȭ
	for (int i = 0; i < n_vertices; i++) distance[i] = INF;
	distance[start_vertex] = 0;	//ù ���� 0���� �ʱ�ȭ

	//�ٽ� �ڵ�
	for (int i = 0; i < n_vertices; i++)
	{
		//���� ����ġ�� ���� ������ ���� ������ ��ȯ
		u = get_min_vertice(graph, n_vertices);
		selected[u] = true;

		//�߰��� �ڵ� : ���� �׷����� �ƴ� ������ �׷����� ��� ����.
		//���� ����ġ�� ���� ���� = INF�� ��Ȳ
		if (distance[u] == INF) return;

		printf("Selected Vertice : %d\n", u);

		//�׷����� ����ġ ������Ʈ
		for (v = 0; v < n_vertices; v++)
		{
			//���� ����� �������� ���ᰡ���� ���� ��..
			if (graph[u][v] != INF)
			{
				//������ ����ġ�� ���� distance �迭 ������Ʈ
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