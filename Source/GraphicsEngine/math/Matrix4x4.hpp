#pragma once
#include "Vector4.hpp"
//#include <algorithm> // For std::swap
namespace CommonUtilities {

template<typename T >
class Matrix3x3;

template<typename T >
class Matrix4x4
{
public:
	// Creates the identity matrix.
	Matrix4x4();
	Matrix4x4(const T& aValue);
	Matrix4x4(const T& m11, const T& m22, const T& m33, const T& m44);
	Matrix4x4(const T& m11, const T& m12, const T& m13, const T& m14, const T& m21, const T& m22, const T& m23, const T& m24, const T& m31, const T& m32, const T& m33, const T& m34, const T& m41, const T& m42, const T& m43, const T& m44);
	// Copies the 3x3 matrix into the top left area of the 4x4 matrix.
	Matrix4x4(const Matrix3x3<T>& aMatrix);
	// Copy Constructor.
	Matrix4x4(const Matrix4x4<T>& aMatrix) = default;
	//Assignment operator (compiler generated)
	Matrix4x4<T>& operator=(const Matrix4x4<T>& aMatrix) = default;
	// () operator for accessing element (row, column) for read/write or read, respectively.
	T& operator()(const int aRow, const int aColumn);
	const T& operator()(const int aRow, const int aColumn) const;

	Vector4<T>& operator[](int aIndex);
	const Vector4<T>& operator[](int aIndex) const;

	Matrix4x4& operator*=(const Matrix4x4& aOther);
	Matrix4x4& operator+=(const Matrix4x4& aOther);
	Matrix4x4& operator-=(const Matrix4x4& aOther);
	Matrix4x4& operator*=(const T& aScalar);


	// Creates a transposed copy of the matrix.
	Matrix4x4<T> GetTranspose() const;
	// Static functions for creating rotation matrices.
	static Matrix4x4<T> CreateRotationAroundX(const T aAngleInRadians);
	static Matrix4x4<T> CreateRotationAroundY(const T aAngleInRadians);
	static Matrix4x4<T> CreateRotationAroundZ(const T aAngleInRadians);
	static Matrix4x4<T> CreateHeadingPitchRoll(const T aPitchInRadians, const T aHeadingInRadians, const T aRollInRadians);
	static Matrix4x4<T> CreatePitchYawRoll(const T aPitchInRadians, const T aYawInRadians, const T aRollInRadians);
	static Matrix4x4<T> CreateTranslation(const T aXcoord, const T aYcoord, const T aZcoord);
	static Matrix4x4<T> CreatePerspective(const T aVerticalFOVInRadians, const T aAspectRatio, const T aNear, const T aFar);
	// Assumes the matrix is made up of nothing but rotations and translations.
	Matrix4x4<T> GetFastInverse() const;

	static const Matrix4x4<T> Identity;

private:
	union {
		Vector4<T> columns[4];
		T values[16];
	};
};

template <typename T>
bool operator==(const Matrix4x4<T>& aFirst, const Matrix4x4<T>& aSecond);
template <typename T>
bool operator!=(const Matrix4x4<T>& a, const Matrix4x4<T>& aSecond);




template <typename T>
Matrix4x4<T> operator+(Matrix4x4<T> aFirst, const Matrix4x4<T>& aSecond);
template <typename T>
Matrix4x4<T> operator-(Matrix4x4<T> aFirst, const Matrix4x4<T>& aSecond);
template <typename T>
Matrix4x4<T> operator*(const Matrix4x4<T>& aFirst, const Matrix4x4<T>& aSecond);


template <typename T>
Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix);

//template <typename T>
//Vector3<T> operator*(const Vector3<T>& aVector, const Matrix4x4<T>& aMatrix);

template <typename T>
Matrix4x4<T> operator*(const T& aScalar, const Matrix4x4<T>& aMatrix);
template <typename T>
Matrix4x4<T> operator*(Matrix4x4<T> aMatrix, const T& aScalar);


template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix4x4<T>& m);


// ====== IMPLEMENTATIONS ======

template<typename T>
inline Matrix4x4<T>::Matrix4x4():Matrix4x4(T(1.0))
{
}

template<typename T>
inline Matrix4x4<T>::Matrix4x4(const T& aValue) : Matrix4x4(aValue, aValue, aValue, aValue)
{

}

template<typename T>
inline Matrix4x4<T>::Matrix4x4(const T& m11, const T& m22, const T& m33, const T& m44) :
	columns{ Vector4<T>(m11, 0, 0, 0), Vector4<T>(0, m22, 0, 0), Vector4<T>(0, 0, m33, 0), Vector4<T>(0, 0, 0, m44) }
{

}

template<typename T>
inline Matrix4x4<T>::Matrix4x4(const T& m11, const T& m12, const T& m13, const T& m14, const T& m21, const T& m22, const T& m23, const T& m24, const T& m31, const T& m32, const T& m33, const T& m34, const T& m41, const T& m42, const T& m43, const T& m44)
	:columns{	Vector4<T>(m11, m21, m31, m41),
				Vector4<T>(m12, m22, m32, m42),
				Vector4<T>(m13, m23, m33, m43),
				Vector4<T>(m14, m24, m34, m44),
	}
{
}



template<typename T>
inline Matrix4x4<T>::Matrix4x4(const Matrix3x3<T>& aMatrix)
{
	columns[0] = aMatrix[0].ToXYZ0();
	columns[1] = aMatrix[1].ToXYZ0();
	columns[2] = aMatrix[2].ToXYZ0();
	columns[3] = { T(0),T(0),T(0),T(1) };
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::GetTranspose() const
{
	return Matrix4x4<T>(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15]);
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(const T aAngleInRadians)
{
	T sin = std::sin(aAngleInRadians);
	T cos = std::cos(aAngleInRadians);
	return Matrix4x4<T>{
		T(1), T(0), T(0), T(0),
			T(0), cos, sin, T(0),
			T(0), -sin, cos, T(0),
			T(0), T(0), T(0), T(1)
	};
}
template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(const T aAngleInRadians)
{
	T sin = std::sin(aAngleInRadians);
	T cos = std::cos(aAngleInRadians);
	return Matrix4x4<T>
	{
		cos, T(0), -sin, T(0),
			T(0), T(1), T(0), T(0),
			sin, T(0), cos, T(0),
			T(0), T(0), T(0), T(1)
	};
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(const T aAngleInRadians)
{
	T sin = std::sin(aAngleInRadians);
	T cos = std::cos(aAngleInRadians);
	return Matrix4x4<T>{
		cos, sin, T(0), T(0),
			-sin, cos, T(0), T(0),
			T(0), T(0), T(1), T(0),
			T(0), T(0), T(0), T(1)
	};
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateHeadingPitchRoll(const T aPitchInRadians, const T aHeadingInRadians, const T aRollInRadians)
{
	const Matrix4x4<T> pitchMatrix = CreateRotationAroundX(aPitchInRadians);
	const Matrix4x4<T> headingMatrix = CreateRotationAroundY(aHeadingInRadians);
	const Matrix4x4<T> rollMatrix = CreateRotationAroundZ(aRollInRadians);
	return headingMatrix * pitchMatrix * rollMatrix;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreatePitchYawRoll(const T aPitchInRadians, const T aYawInRadians, const T aRollInRadians)
{
	const Matrix4x4<T> pitchMatrix = CreateRotationAroundX(aPitchInRadians);
	const Matrix4x4<T> yawMatrix = CreateRotationAroundY(aYawInRadians);
	const Matrix4x4<T> rollMatrix = CreateRotationAroundZ(aRollInRadians);
	return pitchMatrix * yawMatrix * rollMatrix;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateTranslation(const T aXcoord, const T aYcoord, const T aZcoord)
{
	return
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		aXcoord, aYcoord, aZcoord, 1
	};
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreatePerspective(const T aVerticalFOVInRadians, const T aAspectRatio, const T aNear, const T aFar)
{
	const T a = T(1.0) / std::tan(aVerticalFOVInRadians / T(2.0));

	const T zoomX = a  / aAspectRatio; 
	const T zoomY = a;

	const T m33 = aFar / (aFar - aNear);
	const T m43 = -aNear * m33;

	return
	{
		zoomX, 0, 0, 0,
		0, zoomY, 0, 0,
		0, 0, m33, 1,
		0, 0, m43, 0
	};
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse() const
{
	Vector4<T> posInv(-columns[0].w, -columns[1].w, -columns[2].w, T(1));

	const T r11 = columns[0].x;
	const T r21 = columns[0].y;
	const T r31 = columns[0].z;
	const T r12 = columns[1].x;
	const T r22 = columns[1].y;
	const T r32 = columns[1].z;
	const T r13 = columns[2].x;
	const T r23 = columns[2].y;
	const T r33 = columns[2].z;

	return { r11, r21, r31, T(0),
			 r12, r22, r32, T(0),
			 r13, r23, r33, T(0),
			 posInv.Dot(Vector4<T>(r11, r12, r13, T(0))),
			 posInv.Dot(Vector4<T>(r21, r22, r23, T(0))),
			 posInv.Dot(Vector4<T>(r31, r32, r33, T(0))),
			 T(1)
	};
}




template<typename T>
inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
{
	//1 index-.-
	return values[(aRow - 1) + (aColumn - 1) * 4];
}

template<typename T>
inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
{
	//1 index-.-
	return values[(aRow - 1) + (aColumn - 1) * 4];
}


template<typename T>
inline Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4<T>& aOther)
{
	columns[0] += aOther.columns[0];
	columns[1] += aOther.columns[1];
	columns[2] += aOther.columns[2];
	columns[3] += aOther.columns[3];
	return *this;
}

template<typename T>
Matrix4x4<T> operator+(Matrix4x4<T> aFirst, const Matrix4x4<T>& aSecond)
{
	return aFirst += aSecond;
}

template<typename T>
inline Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4<T>& aOther)
{
	columns[0] -= aOther.columns[0];
	columns[1] -= aOther.columns[1];
	columns[2] -= aOther.columns[2];
	columns[3] -= aOther.columns[3];
	return *this;
}

template<typename T>
Matrix4x4<T> operator-(Matrix4x4<T> aFirst, const Matrix4x4<T>& aSecond)
{
	return aFirst -= aSecond;
}

template<typename T>
Matrix4x4<T> operator*(const Matrix4x4<T>& aFirst, const Matrix4x4<T>& aSecond)
{
	Matrix4x4<T> result(aFirst);
	result *= aSecond;
	return result;
}

template<typename T>
Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
{
	return
	{
		aVector.Dot(aMatrix[0]),
		aVector.Dot(aMatrix[1]),
		aVector.Dot(aMatrix[2]),
		aVector.Dot(aMatrix[3])
	};
}

template<typename T>
inline Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& aOther)
{
	const T a00 = columns[0][0];
	const T a01 = columns[0][1];
	const T a02 = columns[0][2];
	const T a03 = columns[0][3];
				
	const T a10 = columns[1][0];
	const T a11 = columns[1][1];
	const T a12 = columns[1][2];
	const T a13 = columns[1][3];
				
	const T a20 = columns[2][0];
	const T a21 = columns[2][1];
	const T a22 = columns[2][2];
	const T a23 = columns[2][3];
				
	const T a30 = columns[3][0];
	const T a31 = columns[3][1];
	const T a32 = columns[3][2];
	const T a33 = columns[3][3];

	const T b00 = aOther[0][0];
	const T b01 = aOther[0][1];
	const T b02 = aOther[0][2];
	const T b03 = aOther[0][3];
 	
	const T b10 = aOther[1][0];
	const T b11 = aOther[1][1];
	const T b12 = aOther[1][2];
	const T b13 = aOther[1][3];
	
	const T b20 = aOther[2][0];
	const T b21 = aOther[2][1];
	const T b22 = aOther[2][2];
	const T b23 = aOther[2][3];
	
	const T b30 = aOther[3][0];
	const T b31 = aOther[3][1];
	const T b32 = aOther[3][2];
	const T b33 = aOther[3][3];

	columns[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
	columns[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
	columns[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
	columns[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
	
	columns[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
	columns[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
	columns[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
	columns[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
	
	columns[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
	columns[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
	columns[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
	columns[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
	
	columns[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
	columns[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
	columns[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
	columns[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
	return *this;
}


template<typename T>
inline Matrix4x4<T>& Matrix4x4<T>::operator*=(const T& aScalar)
{
	columns[0] *= aScalar;
	columns[1] *= aScalar;
	columns[2] *= aScalar;
	columns[3] *= aScalar;
	return *this;
}

template<typename T>
inline Matrix4x4<T> operator*(Matrix4x4<T> aMatrix, const T& aScalar)
{
	return aMatrix *= aScalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& aOutOutStream, const Matrix4x4<T>& aMatrix)
{
	
	return aOutOutStream
		<< "[" << aMatrix(1, 1) << ", " << aMatrix(1, 2) << ", " << aMatrix(1, 3) << ", " << aMatrix(1, 4) << "]" << std::endl
		<< "[" << aMatrix(2, 1) << ", " << aMatrix(2, 2) << ", " << aMatrix(2, 3) << ", " << aMatrix(2, 4) << "]" << std::endl
		<< "[" << aMatrix(3, 1) << ", " << aMatrix(3, 2) << ", " << aMatrix(3, 3) << ", " << aMatrix(3, 4) << "]" << std::endl
		<< "[" << aMatrix(4, 1) << ", " << aMatrix(4, 2) << ", " << aMatrix(4, 3) << ", " << aMatrix(4, 4) << "]";
	
}

template<typename T>
inline Matrix4x4<T> operator*(const T& aScalar, const Matrix4x4<T>& aMatrix)
{
	return aMatrix * aScalar;
}


template<typename T>
Vector4<T>& Matrix4x4<T>::operator[](int aIndex)
{
	return columns[aIndex];
}
template<typename T>
const Vector4<T>& Matrix4x4<T>::operator[](int aIndex) const
{
	return columns[aIndex];
}

template <typename T>
inline bool operator==(const Matrix4x4<T>& aFirst, const Matrix4x4<T>& aSecond) {
	return	aFirst[0] == aSecond[0] &&
			aFirst[1] == aSecond[1] &&
			aFirst[2] == aSecond[2] &&
			aFirst[3] == aSecond[3];
}
template <typename T>
inline bool operator!=(const Matrix4x4<T>& aFirst, const Matrix4x4<T>& aSecond) {
	return !(aFirst == aSecond);
}

template<typename T>
const Matrix4x4<T> Matrix4x4<T>::Identity = Matrix4x4<T>(1);
}