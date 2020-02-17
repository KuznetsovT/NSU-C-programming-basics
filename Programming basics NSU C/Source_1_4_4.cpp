//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "math.h"
//
///*
//���������� ����� ������� �������.
//����� - ������ ����������� ������ ���� ���������� � ��������������.
//������ �������� �� �0. x_i+1 = x_i - F(x_i)/dF(x_i)
//*/
//double zero_Newton(const double x0, double(*F)(double d), double(*dF)(double d), const double eps);
//
///*
//���������� ����� ������� ������� �� ���������� �� a do b;
//����� - ������ ����������� ������ ���� ���������� � ��������������.
//������ �������� �� �0. x_i+1 = x_i - F(x_i)/dF(x_i)
//*/
//double zero_Newton(const double a, const double b, double(*F)(double d), double(*dF)(double d), const double eps);
//
//
////���������� ����� ������� ������� "��������� ������". ��������� ������������� �������.
////���������, ����� F(a) � F(b) ���� ������ ������.
////����������� ����� ������������ ��� �������������� ������� �������� - ���� .
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
//	//���� a, b � eps �� �����, ��� ��� ������, ��� � ���� ��� ������� ����������
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
//	//����� �������, � ����� ����� ����� �������� �����������.
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
