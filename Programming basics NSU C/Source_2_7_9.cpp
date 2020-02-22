#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <iostream>


using namespace std;


template< class Type>
class Matrix {
private:
	size_t n = 0;
    size_t m = 0;
	Type **arr = NULL;
	size_t *relations = NULL;

	bool Empty() const {
		return (n == 0 && m == 0 && arr == 0 && relations == 0);
	}
	Matrix(Type**arr, size_t*relations, size_t n=0,size_t m = 0 );//без учёта reletions
	
	class IteratorBase;
public:

	Matrix<Type> & operator=(const Matrix<Type> & other);
	
	Matrix();
	Matrix(size_t n, size_t m);
	~Matrix();
	Matrix(const Matrix<Type> & other);
	Matrix(const Type & num, size_t n=0, size_t m=0);                // num*E

	size_t N() const;
	size_t M() const;

	template<class Type>
	friend std::ostream & operator<<(std::ostream& out, const Matrix<Type> & matrix);

	template<class Type>
	friend std::istream & operator>>(std::istream&  in, Matrix<Type> & matrix);

	explicit Matrix(Type**data, size_t n=0, size_t m = 0) :Matrix(data, new size_t(1), n, m) {}


	//template<size_t k,size_t l> 
	//explicit operator Matrix<Type>();

	Type * operator[](size_t num);
	
	/*
	class AllIterator : virtual IteratorBase;
	class ReversedAllIterator : virtual IteratorBase;
	class DiagonalIterator : virtual IteratorBase;
	class ReversedDiagonalIterator : virtual IteratorBase;
	class RowIterator : virtual IteratorBase;
	*/

	Matrix<Type> operator+(const Matrix<Type> & other) const;
	Matrix<Type> operator-(const Matrix<Type> & other) const;

	Matrix<Type> operator*(const Type& num)const;
	friend Matrix<Type> operator*(const Type & num, const Matrix<Type> & matrix);


	Matrix<Type> operator*(const Matrix<Type> & other) const;

	
};


int main() {
	size_t size = 2;
	Matrix<int> m, n;
	std::cin >> n >> m;
	std::cout << std::endl << n * m << std::endl << std::endl << m * n << std::endl;
	Matrix<int> k = m, l = m;
	//cout << l << std::endl;
	return 0;
}







template<class Type>
Matrix<Type>::Matrix(Type ** arr, size_t * relations, size_t n, size_t m): n(n), m(m)  arr(arr), relations(relations) {}

template<class Type>
Matrix<Type> & Matrix<Type>::operator=(const Matrix<Type>& other)
{
	if (n == 0 && m == 0 && arr == 0 relations == 0) {
		//if(other.n == 0)
		n = other.n;
		m = other.m;
		arr = other.arr;
		relations = other.relations;
		(*relations)++;
		return *this;
	}
	if ((n != other.n) || (m != other.m)) throw invalid_argument("Different matrix size");
	if (*relations != 0)
	{
		(*relations)--;
	}
	else {
		for (Type ** i = arr, **end = arr + m; i != end; i++) {
			delete[] * i;
		}
		delete[] arr;
		delete relations;
	}
	
	relations = other.relations; (*relations)++; arr = other.arr;
	return *this;
}

template<class Type>
Matrix<Type>::Matrix() {}

template<class Type>
Matrix<Type>::Matrix(size_t n, size_t m) :n(n), m(m), relations(new size_t(0))
{
	arr = new  Type* [m];

	for (Type **i = arr, **end = arr + m; i != end; i++) {
		*i = new Type[n];
	}
}

template<class Type>
Matrix<Type>::Matrix(const Matrix<Type>& other) : Matrix(other.arr, other.relations, other.n, other.m)
{
	(*relations)++;
}

template<class Type>
Matrix<Type>::Matrix(const Type & num, size_t n, size_t m):Matrix(n, m)
{
	for (unsigned i = 0, end = __min(n, m); i < end; i++) {
		arr[i][i] = num;
	}
}

template<class Type>
Matrix<Type>::~Matrix()
{
	if (*relations != 0) 
	{
		(*relations)--;
	}
	else {
		for (Type ** i = arr, **end = arr + m; i != end; i++) {
			delete[] * i;
		}
		delete[] arr;
		delete relations;
	}
}



template<class Type>
size_t Matrix<Type>::N() const
{
	return n;
}

template<class Type>
size_t Matrix<Type>::M() const
{
	return m;
}

//template<class Type, size_t n, size_t m>
//Type ** Matrix<Type, n, m>::__data__()
//{
//	return arr;
//}

template<class Type>
Type * Matrix<Type>::operator[](size_t num)
{
	return (num < m) ? arr[num] : 0;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator+(const Matrix<Type>& other) const
{
	if ((n != other.n) || (m != other.m)) throw invalid_argument("Different matrix size");
	Matrix<Type> sum(n,m);
	for (
		Type** i_this = arr, ** i_other = other.arr,** i_sum = sum.arr,** i_end = arr + m;
		i_this != i_end;
		i_this++, i_other++, i_sum++
		) {

		for (
			Type* j_this = *i_this, *j_other = *i_other,* j_sum = *i_sum,* j_end = *i_this + n;
			j_this != j_end;
			j_this++, j_other++, j_sum++
			) {

			*j_sum = *j_this + *j_other;
		}
	}
	return sum;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type>& other) const
{
	if ((n != other.n) || (m != other.m)) throw invalid_argument("Different matrix size");
	Matrix<Type> minus(n,m);
	for (
		Type** i_this = arr,** i_other = other.arr,** i_minus = minus.arr,** i_end = arr + m;
		i_this != i_end;
		i_this++, i_other++, i_minus++
		) {

		for (
			Type* j_this = *i_this,* j_other = *i_other,* j_minus = *i_minus,* j_end = *i_this + n;
			j_this != j_end;
			j_this++, j_other++, j_minus++
			) {

			*j_minus = *j_this - j_other;
		}
	}
	return minus;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator*(const Type & num) const
{
	Matrix<Type> ans(n, m);
	for (
		Type** i_this = arr,** i_ans = ans.arr,** i_end = arr + m;
		i_this != i_end;
		i_this++, i_ans++
		) {

		for (
			Type* j_this = *i_this,* j_ans = *i_ans,* j_end = *i_this + n;
			j_this != j_end;
			j_this++, j_ans++
			) {

			*j_ans = *j_this*num;
		}
	}
	return ans;
}


template<class Type>
std::ostream & operator<<(std::ostream & out, const Matrix<Type> & matrix)
{
	for (
		Type** i_this = matrix.arr, ** i_end = matrix.arr + m, **i_last = matrix.arr+m-1;
		i_this != i_end;
		i_this++
		) {

		for (
			Type* j_this = *i_this, *j_end = *i_this + n;
			j_this != j_end;
			j_this++
			) {

			out << *j_this << " ";
		}
		/*if(i_this!= i_last)*/ out << std::endl;
	}
	return out;
}

template<class Type>
std::istream & operator>>(std::istream & in, Matrix<Type>& matrix)
{
	for (
		Type** i_this = matrix.arr, ** i_end = matrix.arr + m;
		i_this != i_end;
		i_this++
		) {

		for (
			Type* j_this = *i_this, *j_end = *i_this + n;
			j_this != j_end;
			j_this++
			) {

			in >> *j_this;
		}
	}
	return in;
}

template<class Type>
Matrix<Type> operator*(const Type & num, const Matrix<Type>& matrix)
{
	Matrix<Type> ans(n,m);
	for (
		Type** i = matrix.arr,** i_ans = ans.arr,** i_end = matrix.arr + m;
		i != i_end;
		i++, i_ans++
		) {

		for (
			Type* j = *i,* j_ans = *i_ans,* j_end = *i + n;
			j != j_end;
			j++, j_ans++
			) {

			*j_ans = num*(*j);
		}
	}
	return ans;
}


/*
template<class Type, size_t n, size_t m>
template<size_t k, size_t l>
Matrix<Type>::operator Matrix<Type>()
{
	return Matrix<Type, k, l>(arr);
}
*/

template<class Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type>& other) const
{
	if (n != other.m) throw invalid_argument("Different matrix size");
	Matrix<Type> mult(other.n, m);
	unsigned i = 0, j = 0;
	for (Type**i_mult = mult.arr,** i_end = mult.arr + m; i_mult != i_end; i_mult++, i++) {
		j = 0;
		for (Type *j_mult = *i_mult,* j_end = *i_mult + n; j_mult != j_end; j_mult++, j++) {
			*j_mult = Type();

			for (Type *i_this = arr[i], *i_this_end = arr[i] + n, **j_other = other.arr;
				i_this != i_this_end;
				i_this++, j_other++) {
				*j_mult = *j_mult + (*i_this)*((*j_other)[j]);
			}
		}
	}
	return mult;
}



