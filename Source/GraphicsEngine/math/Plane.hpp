#pragma once
#include "Vector3.hpp"
namespace CommonUtilities
{

template <typename T>
class Plane {
public:
	// Default constructor.
	Plane();
	// Constructor taking three points where the normal is (aPoint1 - aPoint0) x (aPoint2-aPoint0).
	Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
	// Constructor taking a point and a normal.
	Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);
	// Init the plane with three points, the same as the constructor above.
	void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
	// Init the plane with a point and a normal, the same as the constructor above.
	void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal);
	// Returns whether a point is inside the plane: it is inside when the point is on the plane or on the side the normal is pointing away from.
	// Always returns false if used with an uninitialized line
	bool IsInside(const Vector3<T>&aPosition) const;
	// Returns the normal of the plane.
	const Vector3<T>& GetNormal() const;
	const Vector3<T>& GetPoint() const;
private:
	Vector3<T> myNormal;
	Vector3<T> myPoint;
};

template<typename T>
inline Plane<T>::Plane() :myNormal(), myPoint()
{
}

template<typename T>
inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
{
	myNormal = (aPoint1 - aPoint0).Cross(aPoint2 - aPoint0).GetNormalized();
	myPoint = aPoint0;
}

template<typename T>
inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal):myPoint(aPoint0), myNormal(aNormal)
{
}

template<typename T>
inline void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
{
	myNormal = (aPoint1 - aPoint0).Cross(aPoint2 - aPoint0).GetNormalized();
	myPoint = aPoint0;
}

template<typename T>
inline void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
{
	myPoint = aPoint;
	myNormal = aNormal;
}

template<typename T>
inline bool Plane<T>::IsInside(const Vector3<T>& aPosition) const
{
	if (myNormal == Vector3<T>::zero) return false;
	return GetNormal().Dot(aPosition - myPoint) <= 0;
}

template<typename T>
inline const Vector3<T>& Plane<T>::GetNormal() const
{
	return myNormal;
}

template<typename T>
inline const Vector3<T>& Plane<T>::GetPoint() const
{
	return myPoint;
}

}