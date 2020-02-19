#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "math.h"



//���������� ���������� ���������. �� ���������, ������� ��������� �� �����������
void bubble_sort(void * begin, void * end, size_t elemsize);

//�������� ��������, �������� ��������� ���������� true, ����� �������� ����������� � ���������� �������.  
void bubble_sort(void * begin, void * end, size_t elemsize, bool(*in_right_order)(void *e1, void *e2));


//c��������� �� �����������
bool increasing(void *e1, void *e2) {
	return *(int*)e1 <= * (int *)e2;
}

//���������� �� ��������
bool decreasing(void *e1, void *e2) {
	return *(int*)e1 >= * (int *)e2;
}

//�� ���������� ������
bool abs_increasing(void *e1, void *e2) {
	return abs(*(int*)e1) >= abs(*(int *)e2);
}

int main() {
	int arr[3] = { -2,  1, -4  };
	//qsort???
	bubble_sort(arr, arr +3, sizeof(int));
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



void bubble_sort(void * begin, void * end, size_t elemsize)
{
	typedef signed char byte;

	bool native_compare(void * e1, void * e2, size_t elemsize);
	void swap(void*e1, void*e2, size_t size);
	byte *last = (byte*)end - elemsize;
	for (bool is_sorted = false; !is_sorted && begin != last; last -= elemsize) {
		for (byte*i = (byte*)begin; i != last; i += elemsize) {
			if (!native_compare(i, i + elemsize, elemsize)) {
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
		//����� �����. ����� ��������������� ���������, ��� (a XOR b) XOR b = a � (a XOR b) XOR a = b
		*e1_i = *e1_i ^ *e2_i;
		*e2_i = *e1_i ^ *e2_i;
		*e1_i = *e1_i ^ *e2_i;
		*/
	}

}


bool native_compare(void * e1, void * e2, size_t elemsize)
{
	typedef signed char byte;
	for (byte*i1 = (byte*)e1, *i2 = (byte*)e2, *end = (byte*)e1 + elemsize;
		e1 != end; i1++, i2++) {
		if (!(*i1 == *i2)) return (*i1 < *i2);
	}
	return true;
}


