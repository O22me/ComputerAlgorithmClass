#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 60000

// 선택정렬을 위한 자료이동함수
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// 선택정렬
void selection_sort(int list[], int size)
{
	int target, searched, least;	//정렬할 배열 인덱스, 검색된 교환 배열 인덱스, 최솟값

	//list길이의 -1만큼 회전
	for (target = 0; target < size - 1; target++)
	{
		least = target;	//정렬할 배열 인덱스 값을 최솟값으로 시작
		//다음 배열칸부터 끝까지 최솟값 탐색
		for (searched = target + 1; searched < size; searched++)
		{
			//현재 최솟값보다 더 작은 값이 있으면 최솟값 변경(여기 부등호 방향으로 오름/내림차순 가능)
			if (list[searched] < list[least]) least = searched;
		}
		//최솟값 위치변경
		if (target != least)
		{
			//주소값 전달을 통한 값 변환
			swap(&list[target], &list[least]);
		}
	}
}

// 합병정렬
int sorted[MAX_SIZE];
void merge(int list[], int left, int mid, int right)
{
	int left_index = left, right_index = mid + 1, sorted_index = left;

	//왼쪽 리스트와 오른쪽 리스트의 합병
	while (left_index <= mid && right_index <= right)
	{
		if (list[left_index] <= list[right_index])
		{
			sorted[sorted_index++] = list[left_index++];
		}
		else sorted[sorted_index++] = list[right_index++];
	}

	//합병 후 나머지 복사
	if (left_index > mid)
	{
		for (int remainder = right_index; remainder <= right; remainder++)
		{
			sorted[sorted_index++] = list[remainder];
		}
	}
	else
	{
		for (int remainder = left_index; remainder <= mid; remainder++)
		{
			sorted[sorted_index++] = list[remainder];
		}
	}

	//기존의 리스트에 복사
	for (int i = left; i <= right; i++)
	{
		list[i] = sorted[i];
	}
}

//분할 및 합병 재귀함수로 구현
void merge_sort(int list[], int left, int right)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;	//중간값으로 평균값 적용
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int main(void)
{
	//합병정렬 테스트 코드
	int test_list[8] = { 3, 10, 22, 30, 35, 13, 25, 24 };
	merge_sort(test_list, 0, 7);
	printf("Test Merge Sort(8 values) : ");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", test_list[i]);
	}
	printf("\b\n");
	//Seed 값으로 현재시간을 설정
	srand((unsigned int)time(NULL));
	clock_t start, end;

	//스택 크기 제한으로 인한 힙 영역 할당
	int* list = (int*)malloc(MAX_SIZE * sizeof(int));

	//선택정렬 시간 측정
	for (int i = 0; i < MAX_SIZE; i++)
	{
		*(list + i) = rand() % 100;	//1~100 사이의 랜덤 값을 입력
	}
	start = clock();	//시작 시간 측정
	selection_sort(list, MAX_SIZE);
	end = clock();	//종료 시간 측정
	printf("[Selection Sort Running Time : %.3f]\n", (float)(end - start) / CLOCKS_PER_SEC);	//두 시간의 차를 계산

	//합병정렬 시간 측정
	for (int i = 0; i < MAX_SIZE; i++)
	{
		*(list + i) = rand() % 100;
	}
	start = clock();
	merge_sort(list, 0, MAX_SIZE - 1);
	end = clock();
	printf("[Merge Sort Running Time : %.3f]\n", (float)(end - start) / CLOCKS_PER_SEC);

	//힙 할당 해제
	free(list);
	return 0;
}