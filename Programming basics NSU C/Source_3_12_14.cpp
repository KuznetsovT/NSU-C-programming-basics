
//����� � ��������� ������

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 32
//���������� ��� �� float � � int

//�������� � ��� ������� 
#define FXP_SIZE  3
#define MANT_SIZE 4
#define EXP_BIAS  (((1)<<((FXP_SIZE)-(1)))-(1))


//��������� ��� ������������� float
#define FLOAT_MANT 23
#define FLOAT_EXP 8
#define FLOAT_BIAS 127

typedef int float8;


//����� ������ http://www.softelectro.ru/ieee754.html  ������ �������

/*                         ��������(��,��� ���������� �� ����������)
                           |
0	10101001    0101010010010100100
|          |
SIGN       ���������� ����������
*/

/*
����� �������, ��� ��� ������� ����� ������� ��������� ����������(��� ������, ��������, ���������),
� �������� �������� "����������" ��������. �������� ����� ��� 1,01010001... ������ ������� � ������� �������(��� ��������)
*/

/*
���������� "��������� ��������"

1. 000000000 0000000000000000 - +����
2. 100000000 0000000000000000 - -����
3. 011111111 0000000000000000 - +infinity
4. 111111111 0000000000000000 - -infinity
5. 011111111 ...any value except zero...    - NaN
   111111111 ...any value except zero... 


6. ��� ����������� � ���� ���������, ������������� �������� "����������������� ��������" ���� 0,010101... E ...
�� ���������� � ����
   X00000000 XXXXXXXXXXXXXXX - X ������������� ����� ����� ��������. �� �������� �������� �� ������ ��������� � �. 1

*/

/*
�������� ����������. ��� ����, ����� �� ������� �������������� ��� ����� ��� ����������, ����� �������� ����������.
��� float ��� �������� ����� 2^(������������ ���) - 1. 
�� ���� ���� ������������ �������� ���������� 255(�� ���������� ������ ���� ����), �� �������� ����� 128-1 = 127

��������, ���� ���������� ����� 01111111, �� ����� � �������� ����� 127. 127 - 127 = 0, ������ ��� ������� �������!
���, 10000001  - �������� ����� 128. 128 - 127 = 1 - ...�1
...

� ������ ������ ��� ������ ������� �������� ������������.
*/

//�������� ����� ���������� � ��������� ����� �������. ����� � ������� ������ ������ ���� ����.

/*
� float 1�� ��� ��������, ����� 8 ��� �� ���������� � 23 ���� �� ��������
*/


//�������� ������� ������ �����
void printfloat(float f);     //
void printfloat8(float8 f8); //
void printint(int data);    //��� ������

float8 f32tof8(float f);
float f8tof32(float8 f);

//���������, ������� ����� ������������ �������� ������� f_A -> f_B
struct properties {
	unsigned A_exp;
	unsigned A_mant;
	unsigned A_bias;

	unsigned B_exp;
	unsigned B_mant;
	unsigned B_bias;
};

//������� ������������� ������� ��������������
int fAtofB(int A, const properties prop);

//������ �������������� ������� � ��������������� ------------------

int bit(int n);    //���������� ����� ���� 0.n.1000000...000000, ��� �� n+1 ������� ����� �������
int clean(int & data, const properties & prop); //���� ����� ����� ������ ����� int, �������� ���������� ���� �� ���������� ������.
int E_a(int data, const properties & prop );
int M_a(int data, const properties & prop);
int sign(int data, int & target);
int E_a_to_E_b(int data, int &target, const properties & prop);
int exp_copy(int e, int & target, const properties & prop);
int M_a_to_M_b(int m_a, int &target, const properties & prop);
int denormal(int data, int &target, const properties & prop);
int infinity(int &target, const properties & prop);
int nAn(int data, int & target, const properties & prop);
int killers(int data, int & target, const properties & prop); 
//�����, ����������� � ������� ����� ���������������� � ������������������ ����� ���������� � ����������, �� � ������, �������� ������
//----------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////////


int main() {
	float nan = NAN;
	int i = (*(int *)&nan) | (1<<25);
	float f = *((float *)&i);
	//float f = 20.0f;
	printfloat(f);
	float8 f8 = f32tof8(f);
	printfloat8(f8);
	float f2 = f8tof32(f8);
	printfloat(f2);
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////





void printfloat(float f)
{
	int l = *((int *)&f);   //<-����� ������� � �� �� ������, ��� � ����������

	//�������� ��� ������ ������� ��������
	for (int i = 0; i != SIZE; i++, l = l << 1) {
		printf("%d", (l & (INT_MIN)) != 0);
		if (i == 0 || i == 8) printf(" ");
	}
	printf("\n");
}

void printfloat8(float8 f8)
{
	//�������� ��� ������ ������� ��������
	for (int i = 0; i != (FXP_SIZE+MANT_SIZE+1); i++, f8 = f8 << 1) {
		printf("%d", (f8 & (INT_MIN)) != 0);
		if (i == 0 || i == FXP_SIZE) printf(" ");
	}
	printf("\n");
}

void printint(int data)
{
	//�������� ��� ������ ������� ��������
	for (int i = 1; i != 0; i = i << 1, data = data << 1) {
		printf("%d", (data & (INT_MIN)) != 0);
	}
	printf("\n");
}

float8 f32tof8(float f)
{
	int data = *((int *)&f);
	return (float8)fAtofB(data, { FLOAT_EXP, FLOAT_MANT, FLOAT_BIAS, FXP_SIZE, MANT_SIZE, EXP_BIAS });
}

float f8tof32(float8 f)
{
	int result = fAtofB((int)f, { FXP_SIZE, MANT_SIZE, EXP_BIAS, FLOAT_EXP, FLOAT_MANT, FLOAT_BIAS });
	return *((float *)&result);
}




int fAtofB(int data, properties prop)
{
	//����� ������������ �������� ����������
	//������� �� ���������� ������
	clean(data, prop);
	int target = 0;
	sign(data, target);         //������������� ����
	int e_a = E_a(data, prop), m_a = M_a(data, prop);

	if (e_a == 0) {
		//���� ����, ���� �����������������
		if (m_a == 0) {
			return target; // data = +- 0
		}
		else {
			//denormal
			denormal(data, target, prop);
			return target;
		}
	}
	//��������� ������, ����� ��� ���� ���������� ���������,
	if (~e_a == ((-1) << prop.A_exp)) {
		//���� �������������, ���� ���,
		if (m_a == 0) {
			return infinity(target, prop);
		}
		else {
			return nAn(m_a, target, prop);
		}
	}
	//���� ���������� ��������� ������������ ��������
	if (!E_a_to_E_b(data, target, prop)) return target;
	M_a_to_M_b(m_a, target, prop);
	return target;
}

//���������� �����, � ������� ��� ���� ����� n+1 ����� �������
//��� �������, bit(0) = 0100000000000...
//��� ������   bit(2) = 0001000000000...
int bit(int n)
{
	return ((~((INT_MAX >> 1) | INT_MIN)) >> (n));
}

int clean(int & data, const properties & prop)
{
	data = data & (~(INT_MAX >> (prop.A_exp + prop.A_mant)));
	return data;
}

int E_a(int data, const properties & prop) {
	//��� �������� �������������� ���������� 1, ��� �� �������� - 0. 
	//���� �������������� �� ��������(��������� ������������), �� ������������ �������������. 

	//������ ����� ���� �������� �������� ���������� � data
	int E_a = (data & INT_MAX) >> (SIZE - prop.A_exp - 1);
	//           |                 |
	//         ������� ����        �������� � ������� ����, ����� �������� ������������� ��������
	return E_a;
}

int M_a(int data, const properties & prop)
{
	//�������� ���������� ������ ����������
	int M_a = (data & (INT_MAX >> prop.A_exp));
	//�������� ���� � ����������
	return M_a;
}

int sign(int data, int & target)
{
	//SIGN
	target = data & INT_MIN;
	//������������� ����
	return target != 0; //���������� �������� ��������� ����
}


//���� E_a ����������� � ���� E_b, ���������� 1, ����� target = +- infinity � ������������ 0
int E_a_to_E_b(int data, int & target, const properties & prop)
{
	//�� ��� ��������� ��� data �� �������� �����, �������������� ��� �����.
	int e_a = E_a(data, prop);
	int e = e_a - prop.A_bias;


	//���� ������������ ������� ������������� ���������� ��� f_b ������ �, ���������� �������������
	if (((int)(1 <<prop.B_exp)-1 - (int)prop.B_bias) <= e) {
		infinity(target, prop);
		return 0;
	}
	//���� ���������� ������������� ���������� f_b ������ �, �������� ��������� ���������
	//1. ����� �������� � ������� ����������������� ��� f_b
	if (-(int)prop.B_bias == e) {

		killers(data, target, prop);

		return 0;
	}
	//2. ���� � �������� ��� ����������������� �����
	if (-(int)prop.B_bias > e) {
		//����� �� ������� ����������� ��������...
		int move = -(int)prop.B_bias - e;
		int m_a = M_a(data, prop);
		m_a = m_a >> (1);
		m_a = m_a | bit(prop.A_exp); //��������� �������, ��������� � ������������� 1,�
		m_a = m_a >> (move - 1);
		//.......................................
		//����� ����������� � � ���� 1,010010 -> 0,00...0010101001
		M_a_to_M_b(m_a, target, prop);
		return 0;
	}


	//���� ������ �������, �������� �������� ���������� � f_b
	{
		exp_copy(e, target, prop);
		return 1;
	}

}

//��������� �����������, ��������������� � target ���������� �������� ���������� �
int exp_copy(int e, int & target, const properties & prop)
{
	int E_b = e + prop.B_bias;
	//������� ��������� ������ � target. ��� ����� ������������� ������ ���� ���������� �����������.

	int p_e = 1 << (prop.B_exp - 1); //pointer for e_b
	int p_t = bit(0);        //pointer for target
	// ����������� (~((INT_MAX >> 1) | INT_MIN)) ��� ����� ���� 010000000...00000000

	for (; p_e != 0; p_e = p_e >> 1, p_t = p_t >> 1) {
		if ((p_e & E_b) != 0) target = target | p_t;
		//���� �� ������ ������� � �_b ��������� ���, ��� ���� �������� � target
	}
	return 1;
}


//������� ������������� M_a � ���� M_b;
int M_a_to_M_b(int M_a, int & target, const properties & prop) {
	

	//������� ������� ����������
	/*
	  0000000    |011111100|10... - ���� �������������� ��� -  �������, �������� ������� � ���������� �������
		      |������� � �8|

	��� �� ��������� ������ ���������� ����� ��� ���� �������� ���������, �� ��� ����� ���������(���������� ���� 11+1 = 100)
	*/
	//���� ��������� ������ �_a ��������� � �_b, �� ���������� �� ������, ��� ���� M_b ������ M_a

	if (prop.B_mant < prop.A_mant)
	{
		int p_last = bit(prop.A_exp + prop.B_mant);//�������������� ������
		M_a += p_last;

		if ((M_a & bit(prop.A_exp-1)) != 0) M_a -= p_last;  //����������� ����������
	}

	//����� ��������� �����������
	int p_m = bit(prop.A_exp);
	int p_t = bit(prop.B_exp);
	// ����������� (~((INT_MAX >> 1) | INT_MIN)) ��� ����� ���� 01000...000

	//���������� ������ �� ����, ������� ���� � ����� ��������������, ������� i < MIN( B_mant, A_mant )
	for (unsigned i=0; i< __min(prop.B_mant, prop.A_mant); p_m = p_m >> 1, p_t = p_t >> 1, i++) {
		if ((p_m & M_a) != 0) target = target | p_t;
		//���� �� ������ ������� � M_a ��������� ���, ��� ���� �������� � target
	}
	return 1;
}



int infinity(int & target, const properties & prop)
{

	int E_b = (~(INT_MAX >> prop.B_exp)) & INT_MAX;
	/*                   |
					�������������� ���,
					����� ������ ��� ��� �������, ���� ���������� ���������, � ���� �������� �������.
	*/
	//      ����!         +     ����������
	//        |
	target = (target & INT_MIN) | E_b;

	return target;
}

//���� ����������� ����������������� ��� � �����, � ����������, ��� ��� ����������� � �
int denormal(int data, int & target, const properties & prop)
{
	//���� �������� ����������� ���������� ���������
	//1. ���� -A_BIAS < -B_BIAS
	int move = ((int)prop.A_bias - (int)prop.B_bias);
	if (move >= 0) {
		int m_a = M_a(data, prop) >> (move);
		//����� � ����� ����������������� ����� � ��������� ��� ������ ��� �
		M_a_to_M_b(m_a, target, prop);
		return target;
	}
	else {
		//�������� ���� �������� �����, �� �������� ��� ��������
		//���� �������� ���������, �� �� � � ������� ����������������� �����
		//���� �������� �������, ���� ��������� ������, ����� ������ �������� ������� ������ �� ������� 
		int m_a = M_a(data, prop);

		for (int e = -(int)prop.A_bias; e != 1-(int)prop.B_bias; e--) 
		{
			//������� �������� 0,1... � ����� �������� ����� ������ ������� ������ �������
			//������ ���� ��������� ��������������� �����
			if ((m_a & (bit(prop.A_exp))) != 0) {
				exp_copy(e - 1, target, prop);
				//������� �������� ������� �� ������������������ �������������, ����� �������� ���������������
				//� �������� �� 1

				m_a = (m_a ^ (bit(prop.A_exp))) << 1;
				M_a_to_M_b(m_a, target, prop);
				return target;
			}

			m_a = m_a << 1;
			
		}
		//������� ��������� ��������, ������ ��� ���� ������ �������� �������� ���,
		//��� ������ ����� ����������� �� � ���������������, �� � �����������������

		//���� �� ��������� �������� �� ���������
		if ((m_a & (bit(prop.A_exp))) == 0) {
			m_a = m_a << 1;
			//����� � ����� �����������������
			//E = 0, ������� � target ������ �� �����
			M_a_to_M_b(m_a, target, prop);
			return target;
		}
		else {
			//�����, ���������� ������� ��������.
			//����� �������� ������� killers
			//������ ��� ������ ����� �� ��������������

			//������� �������� ������� �� ������������������ �������������, ����� �������� ���������������
			//� �������� �� 1
			m_a = (m_a ^ (bit(prop.A_exp)) << 1);
			killers(m_a, target, prop);
			return target;
		}
	}	
}




int nAn(int M_a, int & target, const properties & prop)
{
	//� ����������� �� ��������� ����������, ��� ����� �������� � NaN ����� ��������� ��������.
	//�������, ���� � �_b �������� ��������� ����, �� �� ���� �������, �����, ������� ��������� ��������� ��� �_b
	
	if (M_a == 0)
		M_a = M_a | ((~((INT_MAX >> 1) | INT_MIN)) >> (prop.A_exp + prop.B_mant-1));

	// ����������� (~((INT_MAX >> 1) | INT_MIN)) ��� ����� ���� 010000000...0000

	M_a_to_M_b(M_a, target, prop);
	target = target | (~(INT_MAX >> prop.B_exp) & INT_MAX); //��������� �������� ���������� ���������
	return target;
}

int killers(int data, int & target, const properties & prop)
{
	int least_normal(int & target, const properties & prop); //���������� ����������� �� ������ ��������������� �����
	int max_denormal(int & target, const properties & prop); //���������� ������������ �� ������ ����������������� �����
	//C������ ������ ��� ��������
	int p = bit(prop.A_exp);
	if ((p & data) != 0) return least_normal(target, prop);
	else return max_denormal(target, prop);
}

//������� �� killers
int least_normal(int & target, const properties & prop) {
	int p = (~((INT_MAX >> 1) | INT_MIN)) >> (prop.B_exp - 1);
	target = target | p;
	return target;
}

//������� �� killers
int max_denormal(int & target, const properties & prop) {
	int p = (~(INT_MAX >> (prop.B_exp+prop.B_mant))) & (INT_MAX >> prop.B_exp);
	target = target | p;
	return target;
}