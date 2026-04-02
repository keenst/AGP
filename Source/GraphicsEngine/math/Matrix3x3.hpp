#pragma once

#include "Vector3.hpp"
#include "Matrix4x4.hpp"


namespace CommonUtilities {

template<typename T>
class Matrix4x4;


template<typename T>
class Matrix3x3
{
	static_assert(std::is_arithmetic<T>::value, "Matrix3x3 only supports arithmetic types.");
public:
	// Creates the identity matrix.
	Matrix3x3();

	//Matrix3X3() : Matrix3X3(T(1.0)) {}
	Matrix3x3(const T& aValue);

	Matrix3x3(const T& m11, const T& m22, const T& m33);

	Matrix3x3(const T& m11, const T& m12, const T& m13,
		const T& m21, const T& m22, const T& m23,
		const T& m31, const T& m32, const T& m33);


	// Copy Constructor.
	Matrix3x3(const Matrix3x3<T>& aMatrix) = default;
	//Assignment operator (compiler generated)
	Matrix3x3<T>& operator=(const Matrix3x3<T>& aMatrix) = default;
	// Copies the top left 3x3 part of the Matrix4x4.
	Matrix3x3(const Matrix4x4<T>& aMatrix);
	// () operator for accessing element (row, column) for read/write or read, respectively.
	T& operator()(const int aRow, const int aColumn);
	const T& operator()(const int aRow, const int aColumn) const;

	Vector3<T>& operator[](int aIndex);
	const Vector3<T>& operator[](int aIndex) const;

	Matrix3x3& operator*=(const Matrix3x3& aOther);
	Matrix3x3& operator+=(const Matrix3x3& aOther);
	Matrix3x3& operator-=(const Matrix3x3& aOther);
	Matrix3x3& operator*=(const T& aScalar);

	//Computes the determinant
	T Determinant() const;
	// Creates a transposed copy of the matrix.
	Matrix3x3<T> GetTranspose() const;
	// Static functions for creating rotation matrices.
	static Matrix3x3<T> CreateRotationAroundX(const T aAngleInRadians);
	static Matrix3x3<T> CreateRotationAroundY(const T aAngleInRadians);
	static Matrix3x3<T> CreateRotationAroundZ(const T aAngleInRadians);

private:
	union {
		Vector3<T> columns[3];
		T values[9];
	};
};

template <typename T>
Matrix3x3<T> operator+(Matrix3x3<T> aFirst, const Matrix3x3<T>& aSecond);
template <typename T>
Matrix3x3<T> operator-(Matrix3x3<T> aFirst, const Matrix3x3<T>& aSecond);
template <typename T>
Matrix3x3<T> operator*(const Matrix3x3<T>& aFirst, const Matrix3x3<T>& aSecond);


template <typename T>
Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix);

//template <typename T>
//Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix);

template <typename T>
Matrix3x3<T> operator*(const T& aScalar, const Matrix3x3<T>& aMatrix);
template <typename T>
Matrix3x3<T> operator*(Matrix3x3<T> aMatrix, const T& aScalar);


template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix3x3<T>& m);


// ====== IMPLEMENTATIONS BELOW ======

template<typename T>
inline Matrix3x3<T>::Matrix3x3():Matrix3x3(T(1.0))
{

}

template<typename T>
inline Matrix3x3<T>::Matrix3x3(const T& aValue) : Matrix3x3(aValue, aValue, aValue)
{

}

template<typename T>
inline Matrix3x3<T>::Matrix3x3(const T& m11, const T& m22, const T& m33) :
	columns{ Vector3<T>(m11, 0, 0), Vector3<T>(0, m22, 0), Vector3<T>(0, 0, m33) } 
{

}

template<typename T>
inline Matrix3x3<T>::Matrix3x3(const T& m11, const T& m12, const T& m13, const T& m21, const T& m22, const T& m23, const T& m31, const T& m32, const T& m33):
	columns{	Vector3<T>(m11, m21, m31),
				Vector3<T>(m12, m22, m32),
				Vector3<T>(m13, m23, m33) } 
{
}

template<typename T>
inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
{
	columns[0] = aMatrix[0].ToXYZ();
	columns[1] = aMatrix[1].ToXYZ();
	columns[2] = aMatrix[2].ToXYZ();
}


template<typename T>
inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
{
	//1 index-.-
	return values[(aRow - 1) + (aColumn - 1)*3];
}

template<typename T>
inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
{
	//1 index-.-
	return values[(aRow - 1)  + (aColumn - 1)*3];
}


template<typename T>
Vector3<T>& Matrix3x3<T>::operator[](int aIndex)
{
	return columns[aIndex];
}
template<typename T>
const Vector3<T>& Matrix3x3<T>::operator[](int aIndex) const
{
	return columns[aIndex];
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::GetTranspose() const
{
	return Matrix3x3<T>(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8]);
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(const T aAngleInRadians)
{
	T sin = std::sin(aAngleInRadians);
	T cos = std::cos(aAngleInRadians);
	return Matrix3x3<T>{
		T(1), T(0), T(0),
		T(0),  cos, -sin,
		T(0),  sin,  cos
	};
}
template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(const T aAngleInRadians)
{
	T sin = std::sin(aAngleInRadians);
	T cos = std::cos(aAngleInRadians);
	return Matrix3x3<T>
	{
		 cos, T(0),  sin,
		T(0), T(1), T(0),
		-sin, T(0),  cos
	};
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(const T aAngleInRadians)
{
	T sin = std::sin(aAngleInRadians);
	T cos = std::cos(aAngleInRadians);
	return Matrix3x3<T>{
			 cos, -sin, T(0),
			 sin,  cos, T(0),
			T(0), T(0), T(1)
	};
}

template<typename T>
inline T Matrix3x3<T>::Determinant() const
{

	const T m11 = columns[0][0];
	const T m12 = columns[1][0];
	const T m13 = columns[2][0];
	const T m21 = columns[0][1];
	const T m22 = columns[1][1];
	const T m23 = columns[2][1];
	const T m31 = columns[0][2];
	const T m32 = columns[1][2];
	const T m33 = columns[2][2];

	return
		m23 * m32 - m13 * m32 - m22 * m33 + m12 * m33 +
		m13 * m22 - m12 * m23 - m23 * m31 + m13 * m31 +
		m21 * m33 - m11 * m33 - m13 * m21 + m11 * m23 +
		m22 * m31 - m12 * m31 - m21 * m32 + m11 * m32 +
		m12 * m21 - m11 * m22 - m13 * m22 * m31 + m12 * m23 * m31 +
		m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33;
}

template<typename T>
Matrix3x3<T> operator+(Matrix3x3<T> aFirst, const Matrix3x3<T>& aSecond)
{
	aFirst += aSecond;
	return aFirst;
}

template<typename T>
Matrix3x3<T> operator-(Matrix3x3<T> aFirst, const Matrix3x3<T>& aSecond)
{
	aFirst -= aSecond;
	return aFirst;
}

template<typename T>
Matrix3x3<T> operator*(const Matrix3x3<T>& aFirst, const Matrix3x3<T>& aSecond)
{
	//use *=
	const T a11 = aFirst[0][0];
	const T a12 = aFirst[1][0];
	const T a13 = aFirst[2][0];
	const T a21 = aFirst[0][1];
	const T a22 = aFirst[1][1];
	const T a23 = aFirst[2][1];
	const T a31 = aFirst[0][2];
	const T a32 = aFirst[1][2];
	const T a33 = aFirst[2][2];

	const T b11 = aSecond[0][0];
	const T b12 = aSecond[1][0];
	const T b13 = aSecond[2][0];
	const T b21 = aSecond[0][1];
	const T b22 = aSecond[1][1];
	const T b23 = aSecond[2][1];
	const T b31 = aSecond[0][2];
	const T b32 = aSecond[1][2];
	const T b33 = aSecond[2][2];

	return
	{
		a11 * b11 + a12 * b21 + a13 * b31,
		a11 * b12 + a12 * b22 + a13 * b32,
		a11 * b13 + a12 * b23 + a13 * b33,
		a21 * b11 + a22 * b21 + a23 * b31,
		a21 * b12 + a22 * b22 + a23 * b32,
		a21 * b13 + a22 * b23 + a23 * b33,
		a31 * b11 + a32 * b21 + a33 * b31,
		a31 * b12 + a32 * b22 + a33 * b32,
		a31 * b13 + a32 * b23 + a33 * b33,
	};
}


template<typename T>
inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3<T>& aOther)
{
	//the order??
	const T a11 = columns[0][0];
	const T a21 = columns[0][1];
	const T a31 = columns[0][2];
	const T a12 = columns[1][0];
	const T a22 = columns[1][1];
	const T a32 = columns[1][2];
	const T a13 = columns[2][0];
	const T a23 = columns[2][1];
	const T a33 = columns[2][2];

	const T b11 = aOther[0][0];
	const T b21 = aOther[0][1];
	const T b31 = aOther[0][2];
	const T b12 = aOther[1][0];
	const T b22 = aOther[1][1];
	const T b32 = aOther[1][2];
	const T b13 = aOther[2][0];
	const T b23 = aOther[2][1];
	const T b33 = aOther[2][2];

	columns[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
	columns[1][0] = a11 * b12 + a12 * b22 + a13 * b32;
	columns[2][0] = a11 * b13 + a12 * b23 + a13 * b33;
	columns[0][1] = a21 * b11 + a22 * b21 + a23 * b31;
	columns[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
	columns[2][1] = a21 * b13 + a22 * b23 + a23 * b33;
	columns[0][2] = a31 * b11 + a32 * b21 + a33 * b31;
	columns[1][2] = a31 * b12 + a32 * b22 + a33 * b32;
	columns[2][2] = a31 * b13 + a32 * b23 + a33 * b33;

	return *this;
}

template<typename T>
inline Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3<T>& aOther)
{
	columns[0] += aOther[0];
	columns[1] += aOther[1];
	columns[2] += aOther[2];
	return *this;
}

template<typename T>
inline Matrix3x3<T>& Matrix3x3<T>::operator-=(const Matrix3x3<T>& aOther)
{
	columns[0] -= aOther[0];
	columns[1] -= aOther[1];
	columns[2] -= aOther[2];
	return *this;
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
{
	return
		{
			aVector.Dot(aMatrix[0]),
			aVector.Dot(aMatrix[1]),
			aVector.Dot(aMatrix[2])
		};
}

template<typename T>
inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const T& aScalar)
{
	columns[0] *= aScalar;
	columns[1] *= aScalar;
	columns[2] *= aScalar;
	return *this;
}

template<typename T>
inline Matrix3x3<T> operator*(Matrix3x3<T> aMatrix, const T& aScalar)
{
	return aMatrix *= aScalar;
}

template<typename T>
inline Matrix3x3<T> operator*(const T& aScalar, const Matrix3x3<T>& aMatrix)
{
	return aMatrix * aScalar;
}


template<typename T>
std::ostream& operator<<(std::ostream& aOutStream, const Matrix3x3<T>& aMatrix)
{
	return aOutStream
		<< "[" << aMatrix(1, 1) << ", " << aMatrix(1, 2) << ", " << aMatrix(1, 3) << "]" << std::endl
		<< "[" << aMatrix(2, 1) << ", " << aMatrix(2, 2) << ", " << aMatrix(2, 3) << "]" << std::endl
		<< "[" << aMatrix(3, 1) << ", " << aMatrix(3, 2) << ", " << aMatrix(3, 3) << "]";
}



}