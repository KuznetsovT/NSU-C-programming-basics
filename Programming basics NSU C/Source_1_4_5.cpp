//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "math.h"
//
//
///*
//������� ������� �������� �� ���������� [a; b] ������� �������� � ����� dx; 
//
//��������� �����������!!!
//����� ��������� X - ��� ��������� ���� ��������, ������� ��������� double.
//����� ������ ������� f(x) = {0, ���� x ����������� �; 1, ���� �� ����������� };
//������ ������� ������������, ��� ��� � ��� �������� ����� ��������(� double �������� ����� ����)
//������, ��������� ������� 0, ���� �������� ����� (b-a)! 
//
//������, ��� ��� ����������� �������� ������������, ���� �� ������ �������
//*/
//double Integrate(double(*f)(double x), double dx, double a, double b);
//
//double Func(double d) {
//	return d;
//}
//
//
//int main() {
//	
//	//���� a, b � eps �� �����, ��� ��� ������, ��� � ���� ��� ������� ����������
//	printf("%lf\n", Integrate(Func, 0.000001, 0, 10));
//	return 0;
//}
//
//double Integrate(double(*f)(double x), double dx, double a, double b)
//{
//	double I = 0;
//	for (double x = a; x <= b - dx; x += dx) {
//		I += (f(x) + f(x + dx))*dx / 2;
//	}
//	return I;
//}
