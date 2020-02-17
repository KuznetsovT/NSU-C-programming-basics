//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "math.h"
//#include "stdlib.h"
//
//double *max(double arr[], const unsigned size);
//double *min(double arr[], const unsigned size);
//double mean(double arr[], const unsigned size);
//double  RMS(double arr[], const unsigned size);
//
//
////чтобы протестировать динамический массив просто удалите(или переименуйте) макрос
//#define ARR_MAX_SIZE 10000
//
//
//
//int main() {
//
//	unsigned size = 0;
//	scanf("%u", &size);
//
//#ifdef ARR_MAX_SIZE
//	if (size > ARR_MAX_SIZE) {
//		printf("TOO BIG\n");
//		return 0;
//	}
//	double arr[ARR_MAX_SIZE];
//#else
//	double *arr = (double *)malloc(size * sizeof(double));
//#endif
//	for (double *i = arr; i != arr + size; i++) scanf("%lf", i);
//	printf("MAX  is %lf\nMIN  is %lf\nMEAN is %lf\nRMS  is %lf\n", *max(arr, size), *min(arr, size), mean(arr, size), RMS(arr, size));
//
//#ifndef ARR_MAX_SIZE
//	free(arr);
//#endif // !ARR_MAX_SIZE
//
//	return 0;
//}
//
//double * max(double arr[], const unsigned size)
//{
//	double *max = arr;
//	for (double *i = arr; i != arr + size; i++) if (*max < *i) *max = *i;
//	return max;
//}
//
//double * min(double arr[], const unsigned size)
//{
//	double *min = arr;
//	for (double *i = arr; i != arr + size; i++) if (*min > *i) *min = *i;
//	return min;
//}
//
//double mean(double arr[], const unsigned size)
//{
//	double val = 0;
//	for (unsigned i = 0; i < size; i++) {
//		val = val * ((double)i / (double)(i + 1)) + arr[i] / (double)(i + 1);
//	}
//	return val;
//}
//
//double RMS(double arr[],const unsigned size)
//{
//	if (1 == size) return 0;
//	double val = 0, m = mean(arr, size);
//	for (unsigned i = 0; i < size; i++) {
//		val = val * ((double)i / (double)(i + 1)) + (arr[i] - m)*(arr[i] - m) / (double)(i + 1);
//	}
//	return sqrt(val  * (size / (size - 1)));
//}
//
