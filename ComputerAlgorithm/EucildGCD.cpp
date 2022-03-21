#include <stdio.h>

int EuclidGDC(int a, int b)
{
	if (a < b) return EuclidGDC(b, a);	//항상 a가 b보다 크게.
	else if (a == b) return a;				//최대공약수 도출
	else if ((a == 1) || (b == 1)) return 1;	//최대공약수가 1.
	else
	{
		EuclidGDC(a - b, b);
	}
}

void main(void)
{
	int a, b;
	scanf_s("%d %d", &a, &b);

	while (1)
	{
		if ((a < 0) || (b < 0)) break;
		printf("%d\n", EuclidGDC(a, b));
		scanf_s("%d %d", &a, &b);
	}
	return;
}