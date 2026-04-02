#pragma once
#include <ostream>
#include "Math.hpp"
namespace Tga
{
	template <typename T>
	class Vector3;
}
namespace CommonUtilities
{
	template <typename T>
	class Vector4;
	template <typename T>
	class Vector3
	{

		static_assert(std::is_arithmetic<T>::value, "Vector3 only supports arithmetic types.");
	public:
		T x; //Note: this variable is explicitly public.
		T y; //Note: this variable is explicitly public.
		T z; //Note: this variable is explicitly public.
		//Creates a null-vector
		Vector3();
		//Creates a vector (aX, aY, aZ)
		Vector3(const T& aX, const T& aY, const T& aZ);

		Vector3(const Tga::Vector3<T>& aTgaVector);

		//Copy constructor (compiler generated)
		Vector3(const Vector3<T>& aVector) = default;

		//Assignment operator (compiler generated)
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;

		T& operator[](int aIndex);
		const T& operator[](int aIndex) const;

		//Destructor (compiler generated)
		~Vector3() = default;
		// Returns a CommonUtilities Vector3 copy with another datatype as elements, 
		// ex: converts from Vector3<int> to Vector3<float>
		// useful to explicitly do operations, such as addition, for an explicit type
		template<class TargetType>
		Vector3<TargetType> ToType() const;
		//Returns a copy of the vector as a Tga vector, use to interface with TGE
		Tga::Vector3<T> ToTga() const;
		//Returns a negated copy of the vector
		Vector3<T> operator-() const;
		//Returns the squared length of the vector, optimization compared to length
		T LengthSqr() const;
		//Returns the length of the vector, int vector is not required to work
		T Length() const;
		//Returns a normalized copy of this vector. Need not function for int vectors
		//Handle normalization of zero-vector by returning the zero vector
		Vector3<T> GetNormalized() const;
		//Normalizes the vector. Need not function for int vectors
		//Handle normalization of zero-vector by not modifying the vector.
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const;
		static T Dot(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
		//Returns the cross product of this and aVector. Only for Vector3
		Vector3<T> Cross(const Vector3<T>& aVector) const;
		static Vector3<T> Cross(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
		static Vector3<T> Scale(const Vector3<T>& aVector0, const Vector3<T>& aVector1);

		static Vector3<T> Reflect(const Vector3<T>& aInDirection, const Vector3<T>& aNormal);

		Vector4<T> ToXYZ0() const;
		Vector4<T> ToXYZ1() const;

		static const Vector3<T> up;
		static const Vector3<T> down;
		static const Vector3<T> right;
		static const Vector3<T> left;
		static const Vector3<T> back;
		static const Vector3<T> forward;
		static const Vector3<T> zero;
		static const Vector3<T> one;

	};

	//returns a negated version of this vector
	//template <typename T>
	//Vector4<T> operator-(const Vector4<T> aVector);

	//Returns the vector sum of aVector0 and aVector1
	template <typename T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
	//Returns the vector difference of aVector0 and aVector1
	template <typename T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
	//Returns the vector aVector0 component-multiplied by aVector1
	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
	//Returns the vector aVector multiplied by the scalar aScalar. Vector * Scalar
	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar);
	//Returns the vector aVector multiplied by the scalar aScalar. Scalar * Vector
	template <typename T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector);
	//Returns the vector aVector divided by the scalar aScalar
	template <typename T>
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar);
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1);
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1);
	//Equivalent to setting aVector to (aVector * aScalar)
	template <typename T>
	void operator*=(Vector3<T>& aVector, const T& aScalar);
	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T>
	void operator/=(Vector3<T>& aVector, const T& aScalar);

	template <typename T>
	bool operator==(const Vector3<T>& aVector0, const Vector3<T>& aVector1);

	template <typename T>
	bool operator!=(const Vector3<T>& aVector0, const Vector3<T>& aVector1);

	//Implementations below this line------------

	template <typename T>
	const T& Vector3<T>::operator[](int aIndex) const
	{
		//assert(i >= 0 && i < 3);
		switch (aIndex)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	template <typename T>
	T& Vector3<T>::operator[](int aIndex)
	{
		//assert(i >= 0 && i < 3);
		switch (aIndex)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}


	template<typename T>
	inline Vector3<T>::Vector3():Vector3<T>(T(0), T(0), T(0))
	{
	}

	template<typename T>
	inline Vector3<T>::Vector3(const Tga::Vector3<T>& aTgaVector) : Vector3<T>(aTgaVector.x, aTgaVector.y, aTgaVector.z)
	{
	}
	template<typename T>
	inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ): x(aX), y(aY), z(aZ)
	{
	}
	template<typename T>
	inline T Vector3<T>::LengthSqr() const
	{
		return x*x+y*y+z*z;
	}
	template<typename T>
	inline T Vector3<T>::Length() const
	{
		return static_cast<T>(std::sqrt(LengthSqr()));
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		Vector3<T> result = *this;
		result.Normalize();
		return result;
	}
	template<typename T>
	inline void Vector3<T>::Normalize()
	{
		if (LengthSqr() <= Math<T>::Epsilon) {
			return;
		}
		T inverseLength = static_cast<T>(1.0) / Length();
		x *= inverseLength;
		y *= inverseLength;
		z *= inverseLength;
	}
	template<typename T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return x*aVector.x + y*aVector.y + z*aVector.z;
	}
	template<typename T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return aVector0.x * aVector1.x + aVector0.y * aVector1.y + aVector0.z * aVector1.z;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		return {
			y * aVector.z - z * aVector.y,
			z * aVector.x - x * aVector.z,
			x * aVector.y - y * aVector.x
		};
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return {
			aVector0.y * aVector1.z - aVector0.z * aVector1.y,
			aVector0.z * aVector1.x - aVector0.x * aVector1.z,
			aVector0.x * aVector1.y - aVector0.y * aVector1.x
		};
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Scale(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return { aVector0.x * aVector1.x, aVector0.y * aVector1.y, aVector0.z * aVector1.z };
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Reflect(const Vector3<T>& aInDirection, const Vector3<T>& aNormal)
	{
		return aInDirection - (T(2) * aInDirection.Dot(aNormal) * aNormal);
	}

	template<typename T>
	inline Vector4<T> Vector3<T>::ToXYZ0() const
	{
		return Vector4<T>(x,y,z, T(0));
	}

	template<typename T>
	inline Vector4<T> Vector3<T>::ToXYZ1() const
	{
		return Vector4<T>(x, y, z, T(1));
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator-() const
	{
		return { -x, -y, -z };
	}

	template<typename T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> result = aVector0;
		result += aVector1;
		return result;
	}
	template<typename T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> result = aVector0;
		result -= aVector1;
		return result;
	}
	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return {
			aVector0.x * aVector1.x,
			aVector0.y * aVector1.y,
			aVector0.z * aVector1.z
		};
	}
	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return {
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar
		};
	}
	template<typename T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return aVector * aScalar;
	}
	template<typename T>
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		return {
				aVector.x / aScalar,
				aVector.y / aScalar,
				aVector.z / aScalar
		};
	}
	template<typename T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}
	template<typename T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	template<typename T>
	void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}

	template<typename T>
	void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
	}

	template<typename T>
	bool operator==(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		if (std::is_floating_point<T>::value)
		{
			return Math<T>::Approximately(aVector0.x, aVector1.x) && Math<T>::Approximately(aVector0.y, aVector1.y) && Math<T>::Approximately(aVector0.z, aVector1.z);
		}
		else if (std::is_integral<T>::value)
		{
			return aVector0.x == aVector1.x && aVector0.y == aVector1.y && aVector0.z == aVector1.z;
		}
	}

	template<typename T>
	bool operator!=(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}

	template<typename T>
	template<class TargetType>
	inline Vector3<TargetType> Vector3<T>::ToType() const
	{
		return Vector3<TargetType>(static_cast<TargetType>(x), static_cast<TargetType>(y), static_cast<TargetType>(z));
	}

	template<typename T>
	inline Tga::Vector3<T> Vector3<T>::ToTga() const
	{
		return Tga::Vector3<T>(x,y,z);
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& aStream, const Vector3<T>& aVector)
	{
		return aStream << "[x:" << aVector.x << ", y:" << aVector.y << ", z:" << aVector.z << "]";
	}



	template<typename T>
	const  Vector3<T> Vector3<T>::up(T(0),T(1),T(0));
	template<typename T>
	const  Vector3<T> Vector3<T>::zero(T(0), T(0), T(0));
	template<typename T>
	const  Vector3<T> Vector3<T>::forward(T(0), T(0), T(1));
	template<typename T>
	const  Vector3<T> Vector3<T>::back(T(0), T(0), T(-1));
	template<typename T>
	const  Vector3<T> Vector3<T>::right(T(1), T(0), T(0));
	template<typename T>
	const  Vector3<T> Vector3<T>::left(T(-1), T(0), T(0));
	template<typename T>
	const  Vector3<T> Vector3<T>::down(T(0), T(-1), T(0));
	template<typename T>
	const  Vector3<T> Vector3<T>::one(T(1), T(1), T(1));
}