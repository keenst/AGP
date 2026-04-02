#pragma once
#include <ostream>
#include "Math.hpp"
namespace Tga
{
	template <typename T>
	class Vector4;
}
namespace CommonUtilities
{
	template <typename T>
	class Vector3;

	template <typename T>
	class Vector4
	{

		static_assert(std::is_arithmetic<T>::value, "Vector4 only supports arithmetic types.");
	public:
		T x; //Note: this variable is explicitly public.
		T y; //Note: this variable is explicitly public.
		T z; //Note: this variable is explicitly public.
		T w; //Note: this variable is explicitly public.
		//Creates a null-vector
		Vector4();
		//Creates a vector (aX, aY, aZ)
		Vector4(const T& aX, const T& aY, const T& aZ, const T& aW);
		//Copy constructor (compiler generated)
		Vector4(const Vector4<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;
		//Destructor (compiler generated)
		~Vector4() = default;


		// Returns a CommonUtilities Vector4 copy with another datatype as elements, 
		// ex: converts from Vector4<int> to Vector4<float>
		// useful to explicitly do operations, such as addition, for an explicit type
		template<class TargetType>
		Vector4<TargetType> ToType() const;
		//Returns a copy of the vector as a Tga vector, use to interface with TGE
		Tga::Vector4<T> ToTga() const;
		//Returns a negated copy of the vector
		Vector4<T> operator-() const;
		//Returns the squared length of the vector, optimization compared to length
		T LengthSqr() const;
		//Returns the length of the vector, int vector is not required to work
		T Length() const;
		//Returns a normalized copy of this vector. Need not function for int vectors
		//Handle normalization of zero-vector by returning the zero vector
		Vector4<T> GetNormalized() const;
		//Normalizes the vector. Need not function for int vectors
		//Handle normalization of zero-vector by not modifying the vector.
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector4<T>& aVector) const;

		Vector3<T> ToXYZ() const;

		T& operator[](int aIndex);
		const T& operator[](int aIndex) const;

		static const Vector4<T> up;
		static const Vector4<T> down;
		static const Vector4<T> right;
		static const Vector4<T> left;
		static const Vector4<T> back;
		static const Vector4<T> forward;
		static const Vector4<T> zero;
		static const Vector4<T> one;


	};
	//Returns the vector sum of aVector0 and aVector1
	template <typename T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	//Returns the vector difference of aVector0 and aVector1
	template <typename T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	//Returns the vector aVector0 component-multiplied by aVector1
	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	//Returns the vector aVector multiplied by the scalar aScalar. Vector * Scalar
	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar);
	//Returns the vector aVector multiplied by the scalar aScalar. Scalar * Vector
	template <typename T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector);
	//Returns the vector aVector divided by the scalar aScalar
	template <typename T>
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar);
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1);
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1);
	//Equivalent to setting aVector to (aVector * aScalar)
	template <typename T>
	void operator*=(Vector4<T>& aVector, const T& aScalar);
	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T>
	void operator/=(Vector4<T>& aVector, const T& aScalar);




	template<typename T>
	bool operator==(const Vector4<T>& aVector0, const Vector4<T>& aVector1);

	template<typename T>
	bool operator!=(const Vector4<T>& aVector0, const Vector4<T>& aVector1);


	//Implementations below this line------------

	template<typename T>
	inline Vector4<T>::Vector4() :Vector4<T>(T(0), T(0), T(0), T(0))
	{
	}
	template<typename T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW) : x(aX), y(aY), z(aZ), w(aW)
	{
	}
	template<typename T>
	inline T Vector4<T>::LengthSqr() const
	{
		return x * x + y * y + z * z + w * w;
	}
	template<typename T>
	inline T Vector4<T>::Length() const
	{
		return static_cast<T>(std::sqrt(LengthSqr()));
	}
	template<typename T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		Vector4<T> result = *this;
		result.Normalize();
		return result;
	}
	template<typename T>
	inline void Vector4<T>::Normalize()
	{
		if (LengthSqr() <= Math<T>::Epsilon * Math<T>::Epsilon) {
			return;
		}
		T inverseLength = static_cast<T>(1.0) / Length();
		x *= inverseLength;
		y *= inverseLength;
		z *= inverseLength;
		w *= inverseLength;
	}
	template<typename T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y + z * aVector.z + w * aVector.w;
	}

	template<typename T>
	inline Vector3<T> Vector4<T>::ToXYZ() const
	{
		return {x,y,z};
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::operator-() const
	{
		return { -x, -y, -z, -w };
	}


	template<typename T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> result = aVector0;
		result += aVector1;
		return result;
	}
	template<typename T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> result = aVector0;
		result -= aVector1;
		return result;
	}
	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return {
			aVector0.x * aVector1.x,
			aVector0.y * aVector1.y,
			aVector0.z * aVector1.z,
			aVector0.w * aVector1.w
		};
	}
	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> result = aVector;
		result *= aScalar;
		return result;
	}
	template<typename T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return aVector * aScalar;
	}
	template<typename T>
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> result = aVector;
		result /= aScalar;
		return result;
	}
	template<typename T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}
	template<typename T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}

	template<typename T>
	void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}

	template<typename T>
	void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
		aVector.w /= aScalar;
	}

	template<typename T>
	template<class TargetType>
	inline Vector4<TargetType> Vector4<T>::ToType() const
	{
		return Vector4<TargetType>(static_cast<TargetType>(x), static_cast<TargetType>(y), static_cast<TargetType>(z), static_cast<TargetType>(w));
	}

	template<typename T>
	inline Tga::Vector4<T> Vector4<T>::ToTga() const
	{
		return Tga::Vector4<T>(x, y, z, w);
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& aStream, const Vector4<T>& aVector)
	{
		return aStream << "[x:" << aVector.x << ", y:" << aVector.y << ", z:" << aVector.z << ", w:" << aVector.w << "]";
	}

	template<typename T>
	bool operator==(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		if (std::is_floating_point<T>::value)
		{
			return Math<T>::Approximately(aVector0.x, aVector1.x) && Math<T>::Approximately(aVector0.y, aVector1.y) && Math<T>::Approximately(aVector0.z, aVector1.z) && Math<T>::Approximately(aVector0.w, aVector1.w);
		}
		else if (std::is_integral<T>::value)
		{
			return aVector0.x == aVector1.x && aVector0.y == aVector1.y && aVector0.z == aVector1.z && aVector0.w == aVector1.w;
		}
	}

	template<typename T>
	bool operator!=(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}

	template <typename T>
	inline const T& Vector4<T>::operator[](int aIndex) const
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
		case 3:
			return w;
		}
	}

	template <typename T>
	inline T& Vector4<T>::operator[](int aIndex)
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
		case 3:
			return w;
		}
	}


	template<typename T>
	const  Vector4<T> Vector4<T>::up(T(0), T(1), T(0), T(0));
	template<typename T>
	const  Vector4<T> Vector4<T>::zero(T(0), T(0), T(0), T(0));
	template<typename T>
	const  Vector4<T> Vector4<T>::one(T(1), T(1), T(1), T(1));
	template<typename T>
	const  Vector4<T> Vector4<T>::forward(T(0), T(0), T(1), T(0));
	template<typename T>
	const  Vector4<T> Vector4<T>::back(T(0), T(0), T(-1), T(0));
	template<typename T>
	const  Vector4<T> Vector4<T>::right(T(1), T(0), T(0), T(0));
	template<typename T>
	const  Vector4<T> Vector4<T>::left(T(-1), T(0), T(0), T(0));
	template<typename T>
	const  Vector4<T> Vector4<T>::down(T(0), T(-1), T(0), T(0));
}