#include <stdio.h>
#include <string.h>

//최소값 반환 함수
int min(int x, int y)
{
	return x < y ? x : y;
}

//문자열 손상방지 const char
int edit_distance(const char* input1, const char* input2)
{
	int dist[21][21];
	//대각선 방향 첫번째 NULL = 0
	dist[0][0] = 0;
	//배열 초기화(edit_distance에 맞춰서 세팅)
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
			if (input1[i - 1] == input2[j - 1]) dist[i][j] = dist[i - 1][j - 1];					//문자가 같으면 대각선 방향 편집거리
			else dist[i][j] = min(dist[i - 1][j - 1], min(dist[i][j - 1], dist[i - 1][j])) + 1;	//문자가 다르면 수정, 삽입, 삭제 중 최소값 +1
		}
	}

	//총 편집거리 방향 출력
	for (int j = 0; j <= strlen(input2); j++)
	{
		for (int i = 0; i <= strlen(input1); i++)
		{
			printf("%d\t", dist[i][j]);
		}
		printf("\n");
	}

	//배열 최말단 값 = 편집거리
	return dist[strlen(input1)][strlen(input2)];
}

int main(void)
{
	printf("Edit Distance : %d\n", edit_distance("strong", "stone"));
	printf("Edit Distance : %d\n", edit_distance("algorithm", "altruistic"));

	return 0;
}