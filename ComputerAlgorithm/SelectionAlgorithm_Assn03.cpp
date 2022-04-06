#include <stdio.h>

//주소값 전달을 통한 swap자료이동 함수
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

//Quicksort에서의 partition함수 기능과 동일
int partition(int list[], int p, int r)
{
	int pivot = list[r];	//가장 마지막 원소를 기준pivot

	//제일 앞에서 부터 rear, front를 구성하여 그 사이가 pivot보다 높은 값을 유지하도록.
	int rear = p - 1;	

	for (int front = p; front < r; front++)
	{
		if (list[front] < pivot)
		{
			swap(&list[front], &list[++rear]);
		}
	}

	//기준pivot의 정확한 위치로 이동
	swap(&list[rear + 1], &list[r]);

	//정렬된 pivot값의 인덱스 값 반환.
	return rear + 1;
}

int select(int list[], int p, int r, int target)
{
	//list에 1개 뿐이 없다면 그 값이 목표값.
	if (p == r)
	{
		return list[p];
	}

	//정렬된 pivot의 인덱스 값
	int q = partition(list, p, r);
	//q가 몇번째로 작은 값인지 확인
	int order = q - p + 1;

	//원하는 target번째 값과 동일하다면 반환
	if (target == order)
	{
		return list[q];
	}
	//찾은 order번째보다 원하는 target번째가 작을 경우 기준원소의 왼쪽에 존재.
	else if (target < order)
	{
		return select(list, p, q - 1, target);
	}
	//찾은 order번째보다 원하는 target번째가 클 경우 기준원소의 오른쪽에 존재.
	else
	{
		return select(list, q + 1, r, target - order);
	}
}

int main(void)
{
	int list[12] = { 6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14 };
	int seventh = select(list, 0, 11, 7);
	printf("7번째 : %d", seventh);
	return 0;
}