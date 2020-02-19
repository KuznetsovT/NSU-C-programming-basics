//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "stdlib.h"
//
//
//template< class T>
//struct Matrix_NxM {
//
//	T **arr = 0;
//	size_t n = 0, m = 0;
//};
//
//
//template<class T>
//void InitMatrix(Matrix_NxM<T> &matrix, size_t n, size_t m);
//
//template<class T>
//void FreeMatrix(Matrix_NxM<T> &matrix);
//
//template<class T>
//T det(const Matrix_NxM<T> &matrix);
//
//int main() {
//
//	Matrix_NxM<int> m;
//	InitMatrix(m, 2, 2);
//	m.arr[0][0] = m.arr[1][1] = 1; m.arr[0][1] = m.arr[1][0] = 0;
//	printf("%d\n", det(m));
//	return 0;
//}
//
//
//
//
//template<class T>
//void InitMatrix(Matrix_NxM<T> &matrix, size_t n, size_t m)
//{
//	matrix.arr = (T **)malloc(sizeof(T *)*n);
//	for (T **i = matrix.arr; i != matrix.arr + n; i++) *i = (T *) calloc(m, sizeof(T));
//	matrix.n = n;
//	matrix.m = m;
//}
//
//template<class T>
//void FreeMatrix(Matrix_NxM<T> & matrix)
//{
//	for (T **i = matrix.arr; i != matrix.arr + matrix.n; i++) free(*i);
//	free(matrix.arr);
//	matrix.m = matrix.n = 0; matrix.arr = 0;
//}
//
//
//template <class T>
//T det(const Matrix_NxM<T> & matrix)
//{
//	if (matrix.n != matrix.m) return 0;
//	if (matrix.n == 1) return matrix.arr[0][0];
//
//	T DET = 0;
//	Matrix_NxM<T> m_num;
//	InitMatrix(m_num, matrix.n - 1, matrix.m - 1);
//	for (unsigned num = 0; num != matrix.m; num++) {
//		for (T **i = matrix.arr, **i_num = m_num.arr; i != matrix.arr + m_num.n; i++, i_num++) {
//			for (T *j = *i, *j_num = *i_num; j != *i + matrix.m; j++) {
//				if (j == *i + num) continue;
//				*j_num = *j;
//				j_num++;
//			}
//		}
//		DET += matrix.arr[matrix.m - 1][num] * det(m_num);
//		
//	}
//	FreeMatrix(m_num);
//	return DET;
//}
