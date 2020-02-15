//#define _CRT_SECURE_NO_WARNINGS
//#include "stdio.h"
//#include "stdlib.h"
//#include "math.h"
//
//
///*��������� ����� �� �� ������ �������-�������� �� ������� ����� ����� �������.
//���������� ����������� ��������. � count ������������ ���������� ����������� ��������.
//*/
//double Pi_Gregory_Leibniz(const unsigned precision, unsigned &count);
//
//double floor(double d, const unsigned prec); //���������� �� ������� ����� ����� �������
//
//
//
//int main() {
//	
//	unsigned count = 0, prec = 0;
//	printf("Print number of digitals, you need\n");
//	scanf("%u", &prec);
//	double pi = Pi_Gregory_Leibniz(prec, count);
//
//	printf("Pi ~= %0.*lf  by %u iterations\n", prec, floor(pi, prec), count);
//	return 0;
//}
//
//
//double Pi_Gregory_Leibniz(const unsigned precision, unsigned &count) {
//	double reversed(const unsigned num);                   // ���������� 1/num
//	bool equal(double d1, double d2, const unsigned prec); //��������� ����� �� ������� �����
//	
//	double pi_up = 4, pi_down = 0;                         //��������� �� ������ � �����
//	for (count = 1; !equal(pi_up, pi_down, precision); count++) {
//		
//		switch (count % 2) {
//		case 0:
//			pi_up = pi_down + 4 * reversed(2 * count + 1);
//			break;
//		case 1:
//			pi_down = pi_up - 4 * reversed(2 * count + 1);
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
//	int _int_ = (int)floor(d); //��������� ����� ����� �����
//	d -= _int_;           //��������� ������ ������� �����
//	d*=pow(10, prec);     //��������� �� 10 � ������ �������, 
//	d = floor(d);         //����� ����� ���������� �� ������ �������� ������ �����
//	d /= pow(10, prec);   //���������� �� �� �����
//	d += _int_;           //� ��� ����
//
//	return d;
//}
//
//double reversed(const unsigned num) {
//	return 1 / (double)num;
//}
//
//
//bool equal(double d1, double d2, const unsigned prec) {
//	//������������ ����� � ���� d_first.d_second
//	int d1_first = (int)floor(d1), d1_second = (int)floor((d1 - floor(d1))*pow(10, prec));
//	int d2_first = (int)floor(d2), d2_second = (int)floor((d2 - floor(d2))*pow(10, prec));
//	return (d1_first == d2_first) && (d1_second == d2_second);
//}
//
