//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "math.h"
//
//
///*
//Функция считает интеграл на промежутке [a; b] методом трапеций с шагом dx; 
//
//ВОЗМОЖНАЯ ПОГРЕШНОСТЬ!!!
//Пусть множество X - это множество всех значений, которые принимает double.
//Тогда возьмём функцию f(x) = {0, если x принадлежит Х; 1, если не принадлежит };
//Данная функция интегрируема, так как в ней конечное число разрывов(в double конечное число байт)
//Однако, программа выведет 0, хотя интеграл равен (b-a)! 
//
//Считаю, что про погрешность говорить бессмысленно, если не знаешь функции
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
//	//ввод a, b и eps не делаю, так как считаю, что в этом нет большой надобности
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
