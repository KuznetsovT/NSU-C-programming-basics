#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <iostream>


using namespace std;



template< class Type>
class Matrix {

public:

	
	
	Matrix();
	~Matrix();
	Matrix(size_t n, size_t m);
	Matrix(const Matrix<Type> & other);
	Matrix(const Type & num, size_t n, size_t m);                // num*E
	Matrix<Type> & operator=(const Matrix<Type> & other);
	Matrix(Type**arr, size_t*relations, size_t n = 0, size_t m = 0);//без учёта reletions

	size_t N() const;
	size_t M() const;

	template<class Type>
	friend std::ostream & operator<<(std::ostream& out, const Matrix<Type> & matrix);

	template<class Type>
	friend std::istream & operator>>(std::istream&  in, Matrix<Type> & matrix);

	explicit Matrix(Type**data, size_t n = 0, size_t m = 0);

	template<class Type>
	friend Matrix<Type> size_cast(Matrix<Type> & other, size_t n, size_t m);

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

	Matrix<Type> operator+(const Type & num) const;
	
	template<class Type>
	friend Matrix<Type> operator+(const Type & num, const Matrix<Type> & matrix);

	Matrix<Type> operator*(const Type& num)const;
	friend Matrix<Type> operator*(const Type & num, const Matrix<Type> & matrix);
	
	Matrix<Type> operator*(const Matrix<Type> & other) const;



	Type DET() const;


	Matrix<Type> reversed() const;


private:

#define NO_BIND NULL

	size_t n = 0;
	size_t m = 0;
	Type **arr = NULL;
	size_t *relations = NO_BIND;

	bool Empty() const;

	
	Type native_det(const Type *** minor_data, size_t n) const;
	
	const Type *** initReferences() const;

	void deleteReferences(const Type ***arr) const;

	const Type ***initMinor(size_t n) const;

	void minor(const Type *** arr, const Type ***min_data, size_t n, size_t l, size_t k) const;
	
	void deleteMinor(const Type***arr, size_t n) const;

	//class IteratorBase;
	void initMatrix();
	void deleteMatrix();


	//Type **data();
};


int main() {
	Matrix<double> a(2, 2);
	cin >> a;
	Matrix<double> r = a.reversed();
	cout << endl <<a.DET() << endl << endl << r << endl << endl << a*r << endl << endl << r*a << endl;
	return 0;
}







template<class Type>
bool Matrix<Type>::Empty() const {
	return (n == 0 && m == 0 && arr == 0 && relations == 0);
}

template<class Type>
Type Matrix<Type>::native_det(const Type *** minor_data, size_t n) const
{
	if (n == 1) return ***minor_data;
	
	const Type ***minor_buff = initMinor(n);
	Type det = Type(); size_t iter = 0;
	for (auto i = minor_data[0], end = minor_data[0] + n; i != end; i++, iter++) {
		minor(minor_data, minor_buff, n, iter, 0);
		if (iter % 2 == 0 ) {
			det = det + (**i)*native_det(minor_buff, n - 1);
		}
		else {
			det = det - (**i)*native_det(minor_buff, n - 1);
		}
	}
	deleteMinor(minor_buff, n);
	return det;
}

template<class Type>
const Type *** Matrix<Type>::initReferences() const
{
	const Type ***min_data = new const Type**[m];
	Type **i_arr = arr, *j_arr = *arr;
	for (const Type ***i = min_data, ***end = min_data + m; i != end; i++, i_arr++) {
		*i = new const Type*[n];
		j_arr = *i_arr;
		for (const Type ** j = *i, ** j_end = *i + n; j != j_end; j++, j_arr++) {
			*j = j_arr;
		}
	}
	return min_data;
}

template<class Type>
void Matrix<Type>::deleteReferences(const Type *** arr) const
{
	for (auto i = arr, end = arr + m; i != end; i++) {
		delete[] * i;
	}
	delete[] arr;
}

template<class Type>
const Type *** Matrix<Type>::initMinor(size_t n) const
{
	const Type ***minor_buff = new const Type**[n - 1];
	for (const Type ***i = minor_buff, ***end = minor_buff + n - 1; i != end; i++) {
		*i = new const Type*[n - 1];
	}
	return minor_buff;
}

template<class Type>
void Matrix<Type>::minor(const Type *** arr, const Type ***min_buff, size_t n, size_t l, size_t k) const
{
	const Type ***i_this = arr, ***i_end = arr + n;
	const Type  *** i_min = min_buff;

	while (i_this != i_end) {

		if (i_this != arr + k) {
			const Type **j_this = *i_this, **j_end = *i_this + n;
			const Type  ** j_min = *i_min;

			while (j_this != j_end) {

				if (j_this != *i_this + l) {
					*j_min = *j_this;
					j_min++;
				}
				j_this++;
			}
			i_min++;
		}
		i_this++;
	}
}

template<class Type>
void Matrix<Type>::deleteMinor(const Type *** arr, size_t n) const
{
	for (auto i = arr, end = arr + n-1; i != end; i++) {
		delete[] * i;
	}
	delete[] arr;
}

template<class Type>
Matrix<Type>::Matrix(Type ** arr, size_t * relations, size_t n, size_t m): n(n), m(m),  arr(arr), relations(relations) {}

template<class Type>
void Matrix<Type>::initMatrix()
{
	
	arr = new  Type*[m];
	for (Type **i = arr, **end = arr + m; i != end; i++) {
		*i = new Type[n];
	}
}

template<class Type>
void Matrix<Type>::deleteMatrix()
{
	for (Type ** i = arr, **end = arr + m; i != end; i++) {
		delete[] * i;
	}
	delete[] arr;
	delete relations;
}

//template<class Type>
//Type ** Matrix<Type>::data()
//{
//	return arr;
//}

template<class Type>
Matrix<Type> & Matrix<Type>::operator=(const Matrix<Type>& other)
{
	if (Empty()) {
		if (!other.Empty()) {
			n = other.n; m = other.m; arr = other.arr; relations = other.relations;
			if (other.relations != NO_BIND) (*relations)++;
			return *this;
		}
		else return *this;
	}
	if ((n != other.n) || (m != other.m)) throw invalid_argument("Different matrix size");
	this->~Matrix();
	
	if (other.relations != NO_BIND) {
		relations = other.relations; (*relations)++;
	}
	arr = other.arr;
	return *this;
}

template<class Type>
Matrix<Type>::Matrix() {}

template<class Type>
Matrix<Type>::Matrix(size_t n, size_t m) :n(n), m(m), relations(new size_t(0))
{
	initMatrix();
}

template<class Type>
Matrix<Type>::Matrix(const Matrix<Type>& other) : Matrix(other.arr, other.relations, other.n, other.m)
{
	if (relations != NO_BIND) (*relations)++;
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
	if (Empty() || relations == NO_BIND) return;

	if (*relations != 0)
	{
		(*relations)--;
	}
	else {
		deleteMatrix();
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

template<class Type>
Matrix<Type>::Matrix(Type ** data, size_t n, size_t m) :Matrix(data, NO_BIND, n, m) {}

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
Matrix<Type> Matrix<Type>::operator+(const Type & num) const
{
	return this->operator+(Matrix<Type>(num, n, m));
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
		Type** i_this = matrix.arr, ** i_end = matrix.arr + matrix.m, **i_last = matrix.arr+matrix.m-1;
		i_this != i_end;
		i_this++
		) {

		for (
			Type* j_this = *i_this, *j_end = *i_this + matrix.n;
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
		Type** i_this = matrix.arr, ** i_end = matrix.arr + matrix.m;
		i_this != i_end;
		i_this++
		) {

		for (
			Type* j_this = *i_this, *j_end = *i_this + matrix.n;
			j_this != j_end;
			j_this++
			) {

			in >> *j_this;
		}
	}
	return in;
}


template<class Type>
Matrix<Type> size_cast(Matrix<Type>& other, size_t n, size_t m)
{
	return Matrix<Type>(other.arr, NO_BIND, n, m);
}

template<class Type>
Matrix<Type> operator+(const Type & num, const Matrix<Type>& matrix)
{
	return Matrix<Type>(num, matrix.n, matrix.m).operator+(matrix);
}

template<class Type>
Matrix<Type> operator*(const Type & num, const Matrix<Type>& matrix)
{
	Matrix<Type> ans(matrix.n,matrix.m);
	for (
		Type** i = matrix.arr,** i_ans = ans.arr,** i_end = matrix.arr + matrix.m;
		i != i_end;
		i++, i_ans++
		) {

		for (
			Type* j = *i,* j_ans = *i_ans,* j_end = *i + matrix.n;
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

template<class Type>
Type Matrix<Type>::DET() const
{
	if (n != m) throw invalid_argument("Different matrix sizes!");

	const Type *** ref = initReferences();
	Type det = native_det(ref, n);
	deleteReferences(ref);
	return det;
}

template<class Type>
Matrix<Type> Matrix<Type>::reversed() const
{
	if (n != m) throw invalid_argument("Different matrix sizes!");
	Type det = DET();
	if (det == 0) return Matrix<Type>(); //empty!
	Matrix<Type> reserved(n, m);
	auto ref = initReferences();
	const Type ***minor_buff = initMinor(n);
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			minor(ref, minor_buff, n, i, j);
			if ((i + j) % 2 == 0)
				reserved.arr[i][j] = native_det(minor_buff, n - 1) / det;
			else
				reserved.arr[i][j] = -native_det(minor_buff, n - 1) / det;
		}
	}
	deleteMinor(minor_buff, n);
	deleteReferences(ref);
	return reserved;
}



