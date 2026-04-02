#pragma once
#include <ostream>
#include "Math.hpp"
namespace Tga
{
	template <typename T>
	class Vector2;
}
namespace CommonUtilities
{
	template <typename T>
	class Vector3;

	template <typename T>
	class Vector2
	{

		static_assert(std::is_arithmetic<T>::value, "Vector2 only supports arithmetic types.");
	public:
		T x; //Note: this variable is explicitly public.
		T y; //Note: this variable is explicitly public.
		//Creates a null-vector
		Vector2();
		//Creates a vector (aX, aY, aZ)
		Vector2(const T& aX, const T& aY);
		//Copy constructor (compiler generated)
		Vector2(const Vector2<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;
		//Destructor (compiler generated)
		~Vector2() = default;
		// Returns a CommonUtilities Vector2 copy with another datatype as elements, 
		// ex: converts from Vector2<int> to Vector2<float>
		// useful to explicitly do operations, such as addition, for an explicit type
		template<class TargetType>
		Vector2<TargetType> ToType() const;
		//Returns a copy of the vector as a Tga vector, use to interface with TGE
		Tga::Vector2<T> ToTga() const;
		//Returns a negated copy of the vector
		Vector2<T> operator-() const;
		//Returns the squared length of the vector, optimization compared to length
		T LengthSqr() const;
		//Returns the length of the vector, int vector is not required to work
		T Length() const;
		//Returns a normalized copy of this vector. Need not function for int vectors
		//Handle normalization of zero-vector by returning the zero vector
		Vector2<T> GetNormalized() const;
		//Normalizes the vector. Need not function for int vectors
		//Handle normalization of zero-vector by not modifying the vector.
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector2<T>& aVector) const;


		Vector3<T> ToXY0();
		Vector3<T> ToXY1();

		static const Vector2<T> up;
		static const Vector2<T> down;
		static const Vector2<T> right;
		static const Vector2<T> left;
		static const Vector2<T> zero;
		static const Vector2<T> one;
	};
	//Returns the vector sum of aVector0 and aVector1
	template <typename T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1);
	//Returns the vector difference of aVector0 and aVector1
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1);
	//Returns the vector aVector0 component-multiplied by aVector1
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1);
	//Returns the vector aVector multiplied by the scalar aScalar. Vector * Scalar
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar);
	//Returns the vector aVector multiplied by the scalar aScalar. Scalar * Vector
	template <typename T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector);
	//Returns the vector aVector divided by the scalar aScalar
	template <typename T>
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar);
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T>
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1);
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T>
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1);
	//Equivalent to setting aVector to (aVector * aScalar)
	template <typename T>
	void operator*=(Vector2<T>& aVector, const T& aScalar);
	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T>
	void operator/=(Vector2<T>& aVector, const T& aScalar);

	//I cannot forawrd declare these nicely because SFINAE
	//template <typename T>
	//bool operator==(const Vector2<T>& aVector0, const Vector2<T>& aVector1);

	//template <typename T>
	//bool operator!=(const Vector2<T>& aVector0, const Vector2<T>& aVector1);

	//Implementations below this line------------

	template<typename T>
	inline Vector2<T>::Vector2() :Vector2<T>(T(0), T(0))
	{
	}
	template<typename T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY) : x(aX), y(aY)
	{
	}
	template<typename T>
	inline T Vector2<T>::LengthSqr() const
	{
		return x * x + y * y;
	}
	template<typename T>
	inline T Vector2<T>::Length() const
	{
		return static_cast<T>(std::sqrt(LengthSqr()));
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		Vector2<T> result = *this;
		result.Normalize();
		return result;
	}
	template<typename T>
	inline void Vector2<T>::Normalize()
	{
		if (LengthSqr() <= Math<T>::Epsilon) {
			return;
		}
		T inverseLength = static_cast<T>(1.0) / Length();
		x *= inverseLength;
		y *= inverseLength;
	}
	template<typename T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y;
	}
	template<typename T>
	inline Vector3<T> Vector2<T>::ToXY0()
	{
		return Vector3<T>(x,y,0);
	}
	template<typename T>
	inline Vector3<T> Vector2<T>::ToXY1()
	{
		return Vector3<T>(x, y, 1);
	}
	template<typename T>
	inline Vector2<T> Vector2<T>::operator-() const 
	{
		return { -x, -y };
	}

	template<typename T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> result = aVector0;
		result += aVector1;
		return result;
	}
	template<typename T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> result = aVector0;
		result -= aVector1;
		return result;
	}
	template<typename T>
	Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return {
			aVector0.x * aVector1.x,
			aVector0.y * aVector1.y,
		};
	}
	template<typename T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> result = aVector;
		result *= aScalar;
		return result;
	}
	template<typename T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return aVector * aScalar;
	}
	template<typename T>
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> result = aVector;
		result /= aScalar;
		return result;
	}
	template<typename T>
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}
	template<typename T>
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}

	template<typename T>
	void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}

	template<typename T>
	void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
	}

	template<typename T>
	template<class TargetType>
	inline Vector2<TargetType> Vector2<T>::ToType() const
	{
		return Vector2<TargetType>(static_cast<TargetType>(x), static_cast<TargetType>(y));
	}

	template<typename T>
	inline Tga::Vector2<T> Vector2<T>::ToTga() const
	{
		return Tga::Vector2<T>(x, y);
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& aStream, const Vector2<T>& aVector)
	{
		return aStream << "[x:" << aVector.x << ", y:" << aVector.y << "]";
	}

	//Uses SFINAE to switch between float and int comparisons
	template<typename T>
	typename std::enable_if_t<std::is_floating_point<T>::value, bool>
		operator==(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Math<T>::Approximately(aVector0.x, aVector1.x) && Math<T>::Approximately(aVector0.y, aVector1.y);
	}

	template<typename T>
	typename std::enable_if_t<std::is_integral<T>::value, bool>
		operator==(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return aVector0.x == aVector1.x && aVector0.y == aVector1.y;
	}

	template<typename T>
	bool operator!=(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}

	template<typename T>
	const  Vector2<T> Vector2<T>::up(T(0), T(1));
	template<typename T>
	const  Vector2<T> Vector2<T>::zero(T(0), T(0));
	template<typename T>
	const  Vector2<T> Vector2<T>::right(T(1), T(0));
	template<typename T>
	const  Vector2<T> Vector2<T>::left(T(-1), T(0));
	template<typename T>
	const  Vector2<T> Vector2<T>::down(T(0), T(-1));
	template<typename T>
	const  Vector2<T> Vector2<T>::one(T(1), T(1));
}