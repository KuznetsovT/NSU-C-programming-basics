//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "math.h"
//
///*
//Нахождение корня методом Ньютона.
//Важно - вторая производная должна быть определена и знакопостоянна.
//Начало итерации от х0. x_i+1 = x_i - F(x_i)/dF(x_i)
//*/
//double zero_Newton(const double x0, double(*F)(double d), double(*dF)(double d), const double eps);
//
///*
//Нахождение корня методом Ньютона на промежутке от a do b;
//Важно - вторая производная должна быть определена и знакопостоянна.
//Начало итерации от х0. x_i+1 = x_i - F(x_i)/dF(x_i)
//*/
//double zero_Newton(const double a, const double b, double(*F)(double d), double(*dF)(double d), const double eps);
//
//
////нахождение корня функции методом "бинарного поиска". Требуется непрерывность функции.
////Требуется, чтобы F(a) и F(b) были разных знаков.
////Аналогичный метод используется при доказательстве теоремы Больцано - Коши .
//double zero_Bolzano_Cauchy(const double a, const double b, double(*F)(double d), const double eps);
//
//double Func(double d) {
//	return 2*d*d*d - 1;
//}
//
//double dFunc(double d) {
//	return 6*d*d;
//}
//
//int main() {
//	
//	//ввод a, b и eps не делаю, так как считаю, что в этом нет большой надобности
//	printf("%lf\n", zero_Newton(0, 10, Func, dFunc, 0.0000001));
//	return 0;
//}
//
//
//
//
//
//double zero_Newton(const double x0, double(*F)(double d), double(*dF)(double d), const double eps)
//{
//	double x = x0;
//	double delta = x0;
//	do {
//		delta = F(x) / dF(x);
//		x = x - delta;
//	} while (delta >= eps/2 || F(x) != 0);
//	return x;
//}
//
//
//
//double zero_Newton(const double a, const double b, double(*F)(double d), double(*dF)(double d), const double eps)
//{
//	//нужно выбрать, с какой точки будем начинать приближение.
//	if (a > b) return zero_Newton(b, a, F, dF, eps);
//	if ((dF(a) < dF(b) && F(a) < F(b))||(dF(a) > dF(b) && F(a) > F(b))) return zero_Newton(b, F, dF, eps);
//	else return zero_Newton(a, F, dF, eps);
//}
//
//double zero_Bolzano_Cauchy(double a,double b, double(*F)(double d), const double eps)
//{
//	//F(a) less than F(b)
//	if (F(a) > F(b)) return zero_Bolzano_Cauchy(b, a, F, eps);
//
//	while (fabs(b - a) >= eps/2) {
//		double mid = (b - a) / 2 + a;
//		double F_mid = F(mid);
//
//		if (F_mid > 0)       {
//			b = mid;
//		}
//		else if (F_mid < 0)  {
//			a = mid;
//		}
//		else if (F_mid == 0) {
//			return mid;
//		}
//	}
//	return (b - a) / 2 + a;
//}
