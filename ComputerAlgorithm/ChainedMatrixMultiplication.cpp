#include <stdio.h>

#define INF 100000

int Cmatrix[100][100];	//계산되는 배열 Calculation(Diagonal Order)
int d_k[10][2];

int min(int x, int y)
{
	return x < y ? x : y;
}

int minCalMatrix(int n)
{
	int x, y;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			x = j, y = j + 1;
			if (x == y) Cmatrix[x][y] = 0;
			else
			{
				Cmatrix[x][y] = INF;
				for (int k = x; k < y; k++)
				{
					Cmatrix[x][y] = min(Cmatrix[x][y], Cmatrix[x][k] + Cmatrix[k + 1][y] + (d_k[x][0] * d_k[k][1] * d_k[y][1]));
				}
			}
		}
	}
	return Cmatrix[0][n - 1];
}

int main(void)
{
	int nMatrix;
	scanf_s("%d", &nMatrix);	//행렬의 개수
	for (int i = 0; i < nMatrix; i++)
	{
		scanf_s("%d %d", &d_k[i][0], &d_k[i][1]);	//각 매트릭스별 구성 크기 설정
	}
	printf("Minimum Calculate : %d", minCalMatrix(nMatrix));

	return 0;
}