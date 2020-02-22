//#define _CRT_SECURE_NO_WARNINGS
//#include "stdio.h"
//#include "stdlib.h"
//#include "math.h"
//
//
///*вычисляет число пи по методу Грегори-Лейбница до нужного знака после запятой.
//Возвращает вычисленное значение. В count записывается количество проделанных итераций.
//*/
//double Pi_Gregory_Leibniz(const unsigned precision, unsigned long long &count);
//
//double floor(double d, const unsigned prec); //округление до нужного знака после запятой
//
//
//
//int main() {
//	
//	unsigned long long count = 0;
//	unsigned prec = 0;
//	printf("Print number of digitals, you need\n");
//	scanf("%u", &prec);
//	double pi = Pi_Gregory_Leibniz(prec, count);
//
//	printf("Pi ~= %0.*lf...  by %llu iterations\n", prec, floor(pi, prec), count);
//	return 0;
//}
//
//
//double Pi_Gregory_Leibniz(const unsigned precision, unsigned long long &count) {
//
//	bool equal(const double d1,const double d2, const unsigned prec); //сравнение чисел до нужного знака
//	
//	double pi_up = 4, pi_down = 0;                                    //оцениваем пи сверху и снизу
//	for (count = 1; !equal(pi_up, pi_down, precision); count++) {
//		if (count == 0) return 0;
//
//		switch (count % 2) {
//		case 0:
//			pi_up = pi_down + 4 /(double)(2 * count + 1);
//			break;
//		case 1:
//			pi_down = pi_up - 4 /(double)(2 * count + 1);
//			break;
//		}
//
//	}
//
//
//	return (pi_up + pi_down) / 2;
//	
//}
//
//
//double floor(double d, const unsigned prec) {
//	d*=pow(10, prec);     //домножаем на 10 в нужной степени, 
//	d = floor(d);         //чтобы после округления до целого оставить нужные знаки
//	d /= pow(10, prec);   //возвращаем всё на место
//
//	return d;
//}
//
//
//bool equal(double d1, double d2, const unsigned prec) {
//	return trunc(d1*pow(10, prec)) == trunc(d2*pow(10, prec));
//}
//
