#include <stdio.h>

//�ּҰ� ������ ���� swap�ڷ��̵� �Լ�
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

//Quicksort������ partition�Լ� ��ɰ� ����
int partition(int list[], int p, int r)
{
	int pivot = list[r];	//���� ������ ���Ҹ� ����pivot

	//���� �տ��� ���� rear, front�� �����Ͽ� �� ���̰� pivot���� ���� ���� �����ϵ���.
	int rear = p - 1;	

	for (int front = p; front < r; front++)
	{
		if (list[front] < pivot)
		{
			swap(&list[front], &list[++rear]);
		}
	}

	//����pivot�� ��Ȯ�� ��ġ�� �̵�
	swap(&list[rear + 1], &list[r]);

	//���ĵ� pivot���� �ε��� �� ��ȯ.
	return rear + 1;
}

int select(int list[], int p, int r, int target)
{
	//list�� 1�� ���� ���ٸ� �� ���� ��ǥ��.
	if (p == r)
	{
		return list[p];
	}

	//���ĵ� pivot�� �ε��� ��
	int q = partition(list, p, r);
	//q�� ���°�� ���� ������ Ȯ��
	int order = q - p + 1;

	//���ϴ� target��° ���� �����ϴٸ� ��ȯ
	if (target == order)
	{
		return list[q];
	}
	//ã�� order��°���� ���ϴ� target��°�� ���� ��� ���ؿ����� ���ʿ� ����.
	else if (target < order)
	{
		return select(list, p, q - 1, target);
	}
	//ã�� order��°���� ���ϴ� target��°�� Ŭ ��� ���ؿ����� �����ʿ� ����.
	else
	{
		return select(list, q + 1, r, target - order);
	}
}

int main(void)
{
	int list[12] = { 6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14 };
	int seventh = select(list, 0, 11, 7);
	printf("7��° : %d", seventh);
	return 0;
}