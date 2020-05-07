
//число с плавающей точкой

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 32
//количество бит во float и в int

//суммарно у нас имеется 
#define FXP_SIZE  3
#define MANT_SIZE 4
#define EXP_BIAS  (((1)<<((FXP_SIZE)-(1)))-(1))
//BIAS можно заменить на число, если нужно

//константы для представления float
#define FLOAT_MANT 23
#define FLOAT_EXP 8
#define FLOAT_BIAS 127

typedef int float8;


//Нашел статью http://www.softelectro.ru/ieee754.html  Вполне неплоха

/*                         Мантисса(то,что умножается на экспоненту)
                           |
0	10101001    0101010010010100100
|          |
SIGN       Показатель экспоненты
*/

/*
Можно сказать, что для каждого числа сначала находится экспонента(при помощи, например, логарифма),
а Мантисса является "уточнением" значения. Мантисса имеет вид 1,01010001... Первую единицу и запятую убирают(для экономии)
*/

/*
Существуют "особенные значения"

1. 000000000 0000000000000000 - +ноль
2. 100000000 0000000000000000 - -ноль
3. 011111111 0000000000000000 - +infinity
4. 111111111 0000000000000000 - -infinity
5. 011111111 ...any value except zero...    - NaN
   111111111 ...any value except zero... 


6. При стремящихся к нулю значениях, дополнительно вводятся "денормализованные значения" вида 0,010101... E ...
Их записывают в виде
   X00000000 XXXXXXXXXXXXXXX - X подразумевает собой любое значение. НО значение Мантиссы не должно совпадать с п. 1

*/

/*
Смещение Экспоненты. Для того, чтобы не вводить дополнительный бит знака для экспоненты, ввели Смещение экспоненты.
Для float это смещение равно 2^(максимальный бит) - 1. 
То есть если максимальное значение экспоненты 255(на экспоненту отведён один байт), то смещение равно 128-1 = 127

например, если экспонента равна 01111111, то тогда её значение равно 127. 127 - 127 = 0, значит это нулевая степень!
или, 10000001  - значение равно 128. 128 - 127 = 1 - ...Е1
...

В данной задаче нас просят сделать смещение произвольным.
*/

//Значение будем записывать и считывать слева направо. Потом в битовой записи пойдут одни нули.

/*
У float 1ый бит знаковый, потом 8 бит на экспоненту и 23 бита на мантиссу
*/


//печатает битовую запись числа
void printfloat(float f);     //
void printfloat8(float8 f8); //
void printint(int data);    //для дебага

float8 f32tof8(float f);
float f8tof32(float8 f);

//структура, которая будет передаваться основной функции f_A -> f_B
struct properties {
	unsigned A_exp;
	unsigned A_mant;
	unsigned A_bias;

	unsigned B_exp;
	unsigned B_mant;
	unsigned B_bias;
};

//Запишем универсальную функцию преобразования
int fAtofB(int A, const properties prop);

//список дополнительных функций к преобразователю ------------------

int bit(int n);    //возвращает число вида 0.n.1000000...000000, где на n+1 позиции стоит единица
int clean(int & data, const properties & prop); //если длина числа меньше длины int, отчищаем незначащие биты от возможного мусора.
int E_a(int data, const properties & prop );   //выделяет экспоненту из числа
int M_a(int data, const properties & prop);    //выделяет мантиссу из числа, но не передвигает
int sign(int data, int & target); 
int E_a_to_E_b(int data, int &target, const properties & prop); //запись экспоненты в В
int exp_copy(int e, int & target, const properties & prop);     //побитовая запись Е в target
int mant_copy(int m_a, int & target, const properties & prop);  //побитовая копия M в target
int mant_round(int & m_a, int & target, const properties & prop);//производим округление для миниммизации потерь
int M_a_to_M_b(int m_a, int &target, const properties & prop);  //округление, обрезка и запись мантиссы из А в В
int denormal(int data, int &target, const properties & prop);   //обработка случая с денормализованными А
int infinity(int &target, const properties & prop);             //записывает в target = +- inf
int nAn(int data, int & target, const properties & prop);       //записывает в target NaN
int killers(int data, int & target, const properties & prop);   //округление непредставимых чисел либо до нормализованных, либо до денормализованных
//числа, находящиеся в границе между нормализованными и денормализованными очень кровожадны и беспощадны, да и вообще, бармалеи мелкие
//----------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////////


int main() {
	
	
	float f = 1.99f;
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
	int l = *((int *)&f);   //<-нужно попасть в ту же память, что и переменная

	//печатаем при помощи битовых операций
	for (int i = 0; i != SIZE; i++, l = l << 1) {
		printf("%d", (l & (INT_MIN)) != 0);
		if (i == 0 || i == 8) printf(" ");
	}
	printf("\n");
}

void printfloat8(float8 f8)
{
	//печатаем при помощи битовых операций
	for (int i = 0; i != (FXP_SIZE+MANT_SIZE+1); i++, f8 = f8 << 1) {
		printf("%d", (f8 & (INT_MIN)) != 0);
		if (i == 0 || i == FXP_SIZE) printf(" ");
	}
	printf("\n");
}

void printint(int data)
{
	//печатаем при помощи битовых операций
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
	//будем пользоваться битовыми операциями
	//очищаем от возможного мусора
	clean(data, prop);
	int target = 0;
	sign(data, target);         //устанавливаем знак
	int e_a = E_a(data, prop), m_a = M_a(data, prop);

	if (e_a == 0) {
		//либо ноль, либо денормализованные
		if (m_a == 0) {
			return target; // data = +- 0
		}
		else {
			//denormal
			denormal(data, target, prop);
			return target;
		}
	}
	//проверяем случай, когда все биты экспоненты единичные,
	if (~e_a == ((-1) << prop.A_exp)) {
		//либо бесконечность, либо НаН,
		if (m_a == 0) {
			return infinity(target, prop);
		}
		else {
			return nAn(m_a, target, prop);
		}
	}
	//если экспонента превысила максимальное значение
	if (!E_a_to_E_b(data, target, prop)) return target;
	M_a_to_M_b(m_a, target, prop);
	return target;
}

//возвращает число, в котором все биты кроме n+1 слева нулевые
//для примера, bit(0) = 0100000000000...
//ещё пример   bit(2) = 0001000000000...
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

	//Первым делом надо получить значение экспоненты в data
	int E_a = (data & INT_MAX) >> (SIZE - prop.A_exp - 1);
	//           |                 |
	//         убираем знак        сдвигаем к правому краю, чтобы получить целочисленное значение
	return E_a;
}

int M_a(int data, const properties & prop)
{
	//действия аналогичны поиску экспоненты
	int M_a = (data & (INT_MAX >> prop.A_exp));
	//зачищаем знак и экспоненту
	return M_a;
}

int sign(int data, int & target)
{
	//SIGN
	target = data & INT_MIN;
	//устанавливаем знак
	return target != 0; //возвращаем значение знакового бита
}


//Если E_a представима в виде E_b, возвращает 1, иначе target = +- infinity и возвращается 0
int E_a_to_E_b(int data, int & target, const properties & prop)
{
	//Мы уже проверили что data не является нулем, бесконечностью или НАНом.
	int e_a = E_a(data, prop);
	int e = e_a - prop.A_bias;


	//Если максимальное битовое представление экспоненты для f_b меньше Е, возвращаем бесконечность
	if (((int)(1 <<prop.B_exp)-1 - (int)prop.B_bias) <= e) {
		infinity(target, prop);
		return 0;
	}
	//если минимально представление экспоненты f_b больше Е, возможно несколько вариантов
	//1. Число попадает в степень денормализованных для f_b
	if (-(int)prop.B_bias == e) {

		killers(data, target, prop);

		return 0;
	}
	//2. Если Е попадает под денормализованные числа
	if (-(int)prop.B_bias > e) {
		//тогда мы смещаем изначальную мантиссу...
		int move = -(int)prop.B_bias - e;
		int m_a = M_a(data, prop);
		m_a = m_a >> (1);
		m_a = m_a | bit(prop.A_exp); //вставляем единицу, опущенную в представлении 1,М
		m_a = m_a >> (move - 1);
		//.......................................
		//чтобы представить её в виде 1,010010 -> 0,00...0010101001
		M_a_to_M_b(m_a, target, prop);
		return 0;
	}

	//если случай обычный, побитово копируем экспоненту в f_b
	{
		exp_copy(e, target, prop);
		return 1;
	}

}

//побитовое копирование, устанавливающее в target переданное значение экспоненты Е
int exp_copy(int e, int & target, const properties & prop)
{
	int E_b = e + prop.B_bias;
	
	//сдвинем E_b так, чтобы он находился на своем месте, и запишем его в target
	E_b = E_b << (SIZE - prop.B_exp - 1);
	target = target | E_b;

	return 1;
}

//побитовое копирование, устанавливающее в target переданное значение мантиссы
int mant_copy(int M_a, int & target, const properties & prop)
{
	//очищаем мантиссу A от незначащих для B знаков
	int focus = (INT_MAX >> prop.A_exp) ^ (INT_MAX >> (prop.A_exp + prop.B_mant)); //00000111111100000000....
	M_a = M_a & focus; //делаем фокус на знаках мантиссы

	//теперь надо эти знаки переместить в расположение мантиссы В
	if (prop.A_exp > prop.B_exp)
		M_a = M_a << (prop.A_exp - prop.B_exp);
	else
		M_a = M_a >> (prop.B_exp - prop.A_exp);


	target = target | M_a;
	return 1;
}


//данная функция производит округление при сужении мантиссы из А в В
int mant_round(int & M_a, int & target, const properties & prop)
{

	//Если последний разряд М_a совпадает с М_b, то округления не делаем, или если M_b больше M_a

	/*
	  0000000    |011111100|10... - если послепоследний бит -  единица, прибавим единицу к последнему разряду
			  |влезает в М8|

	можно отследить исключение вида 11+1 = 100
	Но проверяем, что экспонента примет значение на 1 больше, а мантисса станет нулевой, то есть
	округление и в этом случае происходит корректно
	*/
	
	if (prop.B_mant < prop.A_mant)
	{
		int p_last = bit(prop.A_exp + prop.B_mant);//послепоследний разряд
		M_a += p_last;

		if ((M_a & bit(prop.A_exp - 1)) != 0) {
			//отслеживаем исключение
			M_a = M_a ^ bit(prop.B_exp - 1);
			target += (bit(prop.B_exp - 1));
		}
	}

	return M_a;
}


//находим представление M_a в виде M_b;
int M_a_to_M_b(int M_a, int & target, const properties & prop) {
	

	//Сначала сделаем округление
	mant_round(M_a, target, prop);

	return mant_copy(M_a, target, prop);
}



int infinity(int & target, const properties & prop)
{

	int E_b = (~(INT_MAX >> prop.B_exp)) & INT_MAX;
	/*                   |
					организовываем так,
					чтобы первый бит был нулевой, биты экспоненты единичные, а биты мантиссы нулевые.
	*/
	//      ЗНАК!         +     ЭКСПОНЕНТА
	//        |
	target = (target & INT_MIN) | E_b;

	return target;
}

//надо рассмотреть денормализованные для А числа, и посмотреть, как они представимы в В
int denormal(int data, int & target, const properties & prop)
{
	//надо сравнить минимальные показатели экспонент
	//1. Если -A_BIAS < -B_BIAS
	int move = ((int)prop.A_bias - (int)prop.B_bias);
	if (move >= 0) {
		int m_a = M_a(data, prop) >> (move);

		//тогда В будет денормализованное число с мантиссой ещё меньше чем А
		M_a_to_M_b(m_a, target, prop);

		return target;
	}
	else {
		//мантиссу надо сдвигать влево, но возможно два варианта
		//если мантисса маленькая, то мы в В получим денормализованное число
		//если мантисса большая, надо отследить момент, когда превая значащая единица выйдет за пределы 
		int m_a = M_a(data, prop);

		for (int e = -(int)prop.A_bias; e != 1-(int)prop.B_bias; e--) 
		{
			//смотрим ситуацию 0,1... В такой ситуации после сдвига единица станет главной
			//значит надо построить нормализованное число

			if ((m_a & (bit(prop.A_exp))) != 0) {
				exp_copy(e - 1, target, prop);
				//удаляем значашую единицу из денормализованного представления, чтобы получить нормализованное
				//и сдвигаем на 1

				m_a = (m_a ^ (bit(prop.A_exp))) << 1;

				M_a_to_M_b(m_a, target, prop);
				return target;
			}

			m_a = m_a << 1;
			
		}
		//Смотрим последнюю итерацию, потому что если сейчас появится значащий бит,
		//его нельзя будет представить ни в нормализованном, ни в денормализованном

		//если на последней итерации всё нормально
		if ((m_a & (bit(prop.A_exp))) == 0) {
			m_a = m_a << 1;
			//число В будет денормализованным
			//E = 0, поэтому в target ничего не пишем

			M_a_to_M_b(m_a, target, prop);
			return target;
		}
		else {
			//иначе, получается сложная ситуация.
			//нужно вызывать функцию killers
			//потому что данное число не представляется

			//удаляем значашую единицу из денормализованного представления, чтобы получить нормализованное
			//и сдвигаем на 1
			m_a = (m_a ^ (bit(prop.A_exp)) << 1);

			killers(m_a, target, prop);
			return target;
		}
	}	
}




int nAn(int M_a, int & target, const properties & prop)
{
	//В руководстве по стандарту говорилось, что знаки мантиссы в NaN имеют смысловую нагрузку.
	//Поэтому, если в м_b попадают ненулевые биты, мы их туда запишем, иначе, сделаем ненулевым последний бит м_b
	
	if (M_a < bit(prop.A_exp+prop.B_mant-1))
		M_a = M_a | ((~((INT_MAX >> 1) | INT_MIN)) >> (prop.A_exp + prop.B_mant-1));
	
	// конструкция (~((INT_MAX >> 1) | INT_MIN)) даёт число вида 010000000...0000

	mant_copy(M_a, target, prop);
	
	target = target | (~(INT_MAX >> prop.B_exp) & INT_MAX); //заполняем значение экспоненты единицами
	
	return target;
}

int killers(int data, int & target, const properties & prop)
{
	int least_normal(int & target, const properties & prop); //возвращает минимальное по модулю нормализованное число
	int max_denormal(int & target, const properties & prop); //возвращает максимальное по модулю денормализованное число
	//Cмотрим первый бит мантиссы
	int p = bit(prop.A_exp);
	if ((p & data) != 0) return least_normal(target, prop);
	else return max_denormal(target, prop);
}

//функция из killers
int least_normal(int & target, const properties & prop) {
	int p = (~((INT_MAX >> 1) | INT_MIN)) >> (prop.B_exp - 1);
	target = target | p;
	return target;
}

//функция из killers
int max_denormal(int & target, const properties & prop) {
	int p = (~(INT_MAX >> (prop.B_exp+prop.B_mant))) & (INT_MAX >> prop.B_exp);
	target = target | p;
	return target;
}