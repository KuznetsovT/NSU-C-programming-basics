//#define _CRT_SECURE_NO_WARNINGS
//#include "stdio.h"
//
///*решение уравнения вида kx = b. Возвращает количество решений.
//  Если решений бесконечно много, возвращает -1.
//  Записывает решение в х, если оно единственно.
//*/
//int linear_equation(const double k, const double b, double *x);
//
//
//int main() {
//	double k=0, b=0, x=0;
//	printf("Print k b in kx = b\n");
//	scanf("%lf%lf", &k, &b);
//	switch (linear_equation(k, b, &x)) {
//	case 1:
//		printf("ONE SOLUTION : x = %lf\n", x);
//		break;
//	case 0:
//		printf("NO SOLUTIONS!\n");
//		break;
//	case -1:
//		printf("ANY FLOAT IS SOLUTION!\n");
//		break;
//	default:
//		printf("SOMETHING IS BAD...\n");
//		break;
//	}
//	return 0;
//}
//
//int linear_equation(const double k, const double b, double * x)
//{
//	if (k != 0) 
//	{
//		*x = b / k;
//		return 1;
//	}
//	else 
//	{
//		if (b == 0) {
//			return -1;
//		}
//		else {
//			return 0;
//		}
//	}
//	return 'e'/*error*/;
//}
