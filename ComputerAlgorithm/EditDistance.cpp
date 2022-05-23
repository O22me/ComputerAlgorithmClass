#include <stdio.h>
#include <string.h>

//�ּҰ� ��ȯ �Լ�
int min(int x, int y)
{
	return x < y ? x : y;
}

//���ڿ� �ջ���� const char
int edit_distance(const char* input1, const char* input2)
{
	int dist[21][21];
	//�밢�� ���� ù��° NULL = 0
	dist[0][0] = 0;
	//�迭 �ʱ�ȭ(edit_distance�� ���缭 ����)
	for (int i = 1; i <= strlen(input1); i++)
	{
		dist[i][0] = i;
	}
	for (int j = 1; j <= strlen(input2); j++)
	{
		dist[0][j] = j;
	}

	for (int j = 1; j <= strlen(input2); j++)
	{
		for (int i = 1; i <= strlen(input1); i++)
		{
			if (input1[i - 1] == input2[j - 1]) dist[i][j] = dist[i - 1][j - 1];					//���ڰ� ������ �밢�� ���� �����Ÿ�
			else dist[i][j] = min(dist[i - 1][j - 1], min(dist[i][j - 1], dist[i - 1][j])) + 1;	//���ڰ� �ٸ��� ����, ����, ���� �� �ּҰ� +1
		}
	}

	//�� �����Ÿ� ���� ���
	for (int j = 0; j <= strlen(input2); j++)
	{
		for (int i = 0; i <= strlen(input1); i++)
		{
			printf("%d\t", dist[i][j]);
		}
		printf("\n");
	}

	//�迭 �ָ��� �� = �����Ÿ�
	return dist[strlen(input1)][strlen(input2)];
}

int main(void)
{
	printf("Edit Distance : %d\n", edit_distance("strong", "stone"));
	printf("Edit Distance : %d\n", edit_distance("algorithm", "altruistic"));

	return 0;
}