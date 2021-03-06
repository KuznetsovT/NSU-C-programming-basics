#include "RUN_INFO.h"



#include "stdio.h"
#include "math.h"


#ifdef SOURCE_1_6_8

//Реализация сортировки пузырьком. По умолчанию, функция сортирует по возрастанию

//ОБРАТИТЕ ВНИМАНИЕ, функуция сравнения возвращает true, когда элементы расположены в ПРАВИЛЬНОМ порядке.  
void bubble_sort(void * begin, void * end, size_t elemsize, bool(*in_right_order)(void *e1, void *e2));


//cортировка по возрастанию
bool increasing(void *e1, void *e2) {
	return *(int*)e1 <= * (int *)e2;
}

//сортировка по убыванию
bool decreasing(void *e1, void *e2) {
	return *(int*)e1 >= * (int *)e2;
}

//по увеличению модуля
bool abs_increasing(void *e1, void *e2) {
	return abs(*(int*)e1) >= abs(*(int *)e2);
}



int main() {
	int arr[3] = { -2,  1, -4  };
	//qsort???
	bubble_sort(arr, arr +3, sizeof(int), increasing);
	return 0;
}







void bubble_sort(void * begin, void * end, size_t elemsize, bool(*in_right_order)(void *e1, void *e2))
{
	typedef signed char byte;

	void swap(void*e1, void*e2, size_t size);
	byte *last = (byte*)end - elemsize;
	for (bool is_sorted = false; !is_sorted && begin != last; last-=elemsize) {
		is_sorted = true;
		for (byte*i = (byte*)begin; i != last; i+=elemsize) {
			if (!in_right_order(i, i + elemsize)) {
				swap(i, i + elemsize, elemsize);
				is_sorted = false;
			}
		}
	}
}





void swap(void*e1, void*e2, size_t size) {

	typedef signed char byte;

	for (byte*e2_i = (byte*)e2, *e1_i = (byte*)e1; 
		e2_i != (byte*)e2 + size; e1_i++, e2_i++) {

		byte add = *e1_i;
		*e1_i = *e2_i;
		*e2_i = add;

		/*
		//финты ушами. Можно непосредственно проверить, что (a XOR b) XOR b = a и (a XOR b) XOR a = b
		*e1_i = *e1_i ^ *e2_i;
		*e2_i = *e1_i ^ *e2_i;
		*e1_i = *e1_i ^ *e2_i;
		*/
	}

}



#endif