#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "math.h"

/*решение квадратного уравнения вида axx + bx + c = 0. Возвращает количество решений.
 Если решений бесконечно много, возвращает -1.
 Записывает решение в root1, если оно единственно.
*/
int quadratic_equation(const double a, const double b, const double c, double *root1, double *root2);



/*решение уравнения вида kx = b. Возвращает количество решений.
 Если решений бесконечно много, возвращает -1.
 Записывает решение в х, если оно единственно.
*/
int linear_equation(const double k, const double b, double *x);


int main() {
	double a = 0, b = 0, c = 0;
	double root1 = 0, root2 = 0;
	printf("Print a b c in axx + bx + c = 0\n");
	scanf("%lf%lf%lf", &a, &b, &c);
	switch (quadratic_equation(a, b, c, &root1, &root2)) {
	case 2:
		printf("TWO SOLUTIONS x1 = %lf	x2 = %lf\n", root1, root2);
		break;
	case 1:
		printf("ONE SOLUTION : x = %lf\n", root1);
		break;
	case 0:
		printf("NO SOLUTIONS!\n");
		break;
	case -1:
		printf("ANY FLOAT IS SOLUTION!\n");
		break;
	default:
		printf("SOMETHING IS BAD...\n");
		break;
	}
	return 0;
}


int quadratic_equation(const double a, const double b, const double c, double * root1, double * root2)
{
	if (a != 0)
	{
		double d = b * b - 4 * a * c;
		if (d > 0)
		{
			*root1 = (-b + sqrt(d)) / (2 * a);
			*root2 = (-b - sqrt(d)) / (2 * a);
			return 2;
		}
		else if (d == 0)
		{
			*root1 = (-b) / (2 * a);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return linear_equation(b, -c, root1);
	}
	return 'e'/*error*/;
}


int linear_equation(const double k, const double b, double * x)
{
	if (k != 0)
	{
		*x = b / k;
		return 1;
	}
	else
	{
		if (b == 0) {
			return -1;
		}
		else {
			return 0;
		}
	}
	return 'e'/*error*/;
}

