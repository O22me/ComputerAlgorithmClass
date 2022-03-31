#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 60000

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int leftPivotPartition(int list[], int left, int right)
{
	int pivot = list[left];	//제일 왼쪽을 pivot으로 설정
	int low = left, high = right + 1;	//인덱스 설정

	do
	{
		do
		{
			low++;
		} while (low <= right && list[low] < pivot);		//pivot값보다 큰 값나올때까지 인덱스 이동
		do
		{
			high--;
		} while (high >= left && list[high] > pivot);		//pivot값보다 작은 값 나올때까지 인덱스 이동

		if (low < high) swap(&list[low], &list[high]);		//값 교환으로 정렬
	} while (low < high);

	swap(&list[left], &list[high]);		//pivot 정 위치 설정

	return high;
}

void leftPivotQuicksort(int list[], int left, int right)
{
	if (left < right)
	{
		int sortedIndex = leftPivotPartition(list, left, right);

		leftPivotQuicksort(list, left, sortedIndex - 1);
		leftPivotQuicksort(list, sortedIndex + 1, right);
	}
}

//양 끝과 중간의 인덱스 3개를 비교하여 값이 중간인 인덱스를 반환
int medianOfThree(int list[], int left, int right)
{
	int threeList[3] = { left, (left + right) / 2, right };
	if (list[threeList[0]] > list[threeList[1]]) swap(&threeList[0], &threeList[1]);
	if (list[threeList[1]] > list[threeList[2]]) swap(&threeList[1], &threeList[2]);
	if (list[threeList[0]] > list[threeList[1]]) swap(&threeList[0], &threeList[1]);
	return threeList[1];
}

int medianPivotPartition(int list[], int left, int right)
{
	int median = medianOfThree(list, left, right);
	int pivot = list[median];				//pivot 값 설정
	int low = left, high = right + 1;	//양 끝단에 이동 인덱스 설정

	swap(&list[left], &list[median]);		//선택된 중간값을 가장 왼쪽으로 이동
	//이하 leftPivotPartition과 동일.
	do
	{
		do
		{
			low++;
		} while (low <= right && list[low] < pivot);		//pivot값보다 큰 값나올때까지 인덱스 이동
		do
		{
			high--;
		} while (high >= left && list[high] > pivot);		//pivot값보다 작은 값 나올때까지 인덱스 이동

		if (low < high) swap(&list[low], &list[high]);		//값 교환으로 정렬
	} while (low < high);

	swap(&list[left], &list[high]);		//pivot 정 위치 설정

	return high;
}

void medianPivotQuicksort(int list[], int left, int right)
{
	if (left < right)
	{
		int sortedIndex = medianPivotPartition(list, left, right);	//정렬된 인덱스 값 전달 받음
		
		//정렬된 인덱스를 제외한 퀵정렬
		medianPivotQuicksort(list, left, sortedIndex - 1);
		medianPivotQuicksort(list, sortedIndex + 1, right);	
	}
}

int main(void)
{
	int test_list1[8] = { 3, 10, 22, 30, 35, 13, 25, 24 };
	int test_list2[8] = { 72, 13, 58, 33, 45, 9, 98, 19 };
	//가장 왼쪽 값을 pivot으로 삼는 퀵정렬 테스트
	leftPivotQuicksort(test_list1, 0, 7);
	printf("Test [leftPivot] Quick Sort(8 values) : ");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", test_list1[i]);
	}
	printf("\b\n");

	//중간 값(median)값을 pivot으로 삼는 퀵정렬 테스트
	medianPivotQuicksort(test_list2, 0, 7);
	printf("Test [medianPivot] Quick Sort(8 values) : ");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", test_list2[i]);
	}
	printf("\b\n");
	return 0;
}