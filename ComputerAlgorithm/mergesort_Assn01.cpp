#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 60000

// ���������� ���� �ڷ��̵��Լ�
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// ��������
void selection_sort(int list[], int size)
{
	int target, searched, least;	//������ �迭 �ε���, �˻��� ��ȯ �迭 �ε���, �ּڰ�

	//list������ -1��ŭ ȸ��
	for (target = 0; target < size - 1; target++)
	{
		least = target;	//������ �迭 �ε��� ���� �ּڰ����� ����
		//���� �迭ĭ���� ������ �ּڰ� Ž��
		for (searched = target + 1; searched < size; searched++)
		{
			//���� �ּڰ����� �� ���� ���� ������ �ּڰ� ����(���� �ε�ȣ �������� ����/�������� ����)
			if (list[searched] < list[least]) least = searched;
		}
		//�ּڰ� ��ġ����
		if (target != least)
		{
			//�ּҰ� ������ ���� �� ��ȯ
			swap(&list[target], &list[least]);
		}
	}
}

// �պ�����
int sorted[MAX_SIZE];
void merge(int list[], int left, int mid, int right)
{
	int left_index = left, right_index = mid + 1, sorted_index = left;

	//���� ����Ʈ�� ������ ����Ʈ�� �պ�
	while (left_index <= mid && right_index <= right)
	{
		if (list[left_index] <= list[right_index])
		{
			sorted[sorted_index++] = list[left_index++];
		}
		else sorted[sorted_index++] = list[right_index++];
	}

	//�պ� �� ������ ����
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

	//������ ����Ʈ�� ����
	for (int i = left; i <= right; i++)
	{
		list[i] = sorted[i];
	}
}

//���� �� �պ� ����Լ��� ����
void merge_sort(int list[], int left, int right)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;	//�߰������� ��հ� ����
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int main(void)
{
	//�պ����� �׽�Ʈ �ڵ�
	int test_list[8] = { 3, 10, 22, 30, 35, 13, 25, 24 };
	merge_sort(test_list, 0, 7);
	printf("Test Merge Sort(8 values) : ");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", test_list[i]);
	}
	printf("\b\n");
	//Seed ������ ����ð��� ����
	srand((unsigned int)time(NULL));
	clock_t start, end;

	//���� ũ�� �������� ���� �� ���� �Ҵ�
	int* list = (int*)malloc(MAX_SIZE * sizeof(int));

	//�������� �ð� ����
	for (int i = 0; i < MAX_SIZE; i++)
	{
		*(list + i) = rand() % 100;	//1~100 ������ ���� ���� �Է�
	}
	start = clock();	//���� �ð� ����
	selection_sort(list, MAX_SIZE);
	end = clock();	//���� �ð� ����
	printf("[Selection Sort Running Time : %.3f]\n", (float)(end - start) / CLOCKS_PER_SEC);	//�� �ð��� ���� ���

	//�պ����� �ð� ����
	for (int i = 0; i < MAX_SIZE; i++)
	{
		*(list + i) = rand() % 100;
	}
	start = clock();
	merge_sort(list, 0, MAX_SIZE - 1);
	end = clock();
	printf("[Merge Sort Running Time : %.3f]\n", (float)(end - start) / CLOCKS_PER_SEC);

	//�� �Ҵ� ����
	free(list);
	return 0;
}