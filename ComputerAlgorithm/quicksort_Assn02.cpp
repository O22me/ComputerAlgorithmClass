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
	int pivot = list[left];	//���� ������ pivot���� ����
	int low = left, high = right + 1;	//�ε��� ����

	do
	{
		do
		{
			low++;
		} while (low <= right && list[low] < pivot);		//pivot������ ū �����ö����� �ε��� �̵�
		do
		{
			high--;
		} while (high >= left && list[high] > pivot);		//pivot������ ���� �� ���ö����� �ε��� �̵�

		if (low < high) swap(&list[low], &list[high]);		//�� ��ȯ���� ����
	} while (low < high);

	swap(&list[left], &list[high]);		//pivot �� ��ġ ����

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

//�� ���� �߰��� �ε��� 3���� ���Ͽ� ���� �߰��� �ε����� ��ȯ
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
	int pivot = list[median];				//pivot �� ����
	int low = left, high = right + 1;	//�� ���ܿ� �̵� �ε��� ����

	swap(&list[left], &list[median]);		//���õ� �߰����� ���� �������� �̵�
	//���� leftPivotPartition�� ����.
	do
	{
		do
		{
			low++;
		} while (low <= right && list[low] < pivot);		//pivot������ ū �����ö����� �ε��� �̵�
		do
		{
			high--;
		} while (high >= left && list[high] > pivot);		//pivot������ ���� �� ���ö����� �ε��� �̵�

		if (low < high) swap(&list[low], &list[high]);		//�� ��ȯ���� ����
	} while (low < high);

	swap(&list[left], &list[high]);		//pivot �� ��ġ ����

	return high;
}

void medianPivotQuicksort(int list[], int left, int right)
{
	if (left < right)
	{
		int sortedIndex = medianPivotPartition(list, left, right);	//���ĵ� �ε��� �� ���� ����
		
		//���ĵ� �ε����� ������ ������
		medianPivotQuicksort(list, left, sortedIndex - 1);
		medianPivotQuicksort(list, sortedIndex + 1, right);	
	}
}

int main(void)
{
	int test_list1[8] = { 3, 10, 22, 30, 35, 13, 25, 24 };
	int test_list2[8] = { 72, 13, 58, 33, 45, 9, 98, 19 };
	//���� ���� ���� pivot���� ��� ������ �׽�Ʈ
	leftPivotQuicksort(test_list1, 0, 7);
	printf("Test [leftPivot] Quick Sort(8 values) : ");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", test_list1[i]);
	}
	printf("\b\n");

	//�߰� ��(median)���� pivot���� ��� ������ �׽�Ʈ
	medianPivotQuicksort(test_list2, 0, 7);
	printf("Test [medianPivot] Quick Sort(8 values) : ");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", test_list2[i]);
	}
	printf("\b\n");
	return 0;
}