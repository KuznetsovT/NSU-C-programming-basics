#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"


/*
Функция, вычисляющая простые числа на промежутке от 1 до n не включительно. 
Возвращает количество ЗАПИСАННЫХ в массив 'buffer' простых чисел. 
Обрабатывает переполнение массива. 
При нахождении buffer_size + 1 простого числа, возвращает buffer_size+1, без записи в массив.
*/
unsigned prime_numbers(const unsigned n, unsigned buffer[], const unsigned buffer_size);


int main() {
	unsigned n = 0;
	printf("Program prints first prime numbers from 1 to N, without N.\nPlease, print N\n");
	scanf("%u",&n);
	unsigned *buff = (unsigned*)malloc(n*sizeof(unsigned));
	unsigned count = prime_numbers(n, buff, n);
	printf("%u primes found\n", count);
	for (unsigned*i = buff; i != buff + count; i++) {
		printf("%u ",*i);
	}
	printf("\n");
	free(buff);
	return 0;
}

unsigned prime_numbers(const unsigned n, unsigned buffer[], const unsigned buffer_size)
{
	unsigned count = 0, *end = buffer + count;
	for (unsigned i = 2; i < n; i++) {


		bool is_prime = true;
		for (unsigned*iter = buffer; iter != end && is_prime; iter++) {

			if ((*iter)*(*iter) > i) break;         //если число i составное, сущ. множитель меньше чем sqrt(i)
			is_prime = !(i % *iter == 0);
		}

		if (is_prime) {
			count++;
			if (count <= buffer_size) {
				*end = i;
				end++;
			}
			else return count;
		}
	}
	return count;
}
