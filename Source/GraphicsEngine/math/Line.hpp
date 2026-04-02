#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{

	template <typename T>
	class Line {
	public:
		// Default constructor: there is no line, the normal is the zero vector.
		Line();
		// Constructor that takes two points that define the line, the direction is aPoint1 - aPoint0.
		Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		// Init the line with two points, the same as the constructor above.
		void InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		// Init the line with a point and a direction.
		void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>&aDirection);
		// Init the line with a point and a direction.
		void InitWithPointAndNormal(const Vector2<T>& aPoint, const Vector2<T>& aNormal);
		// Returns whether a point is inside the line: it is inside when the point 
		// is on the line or on the side the normal is pointing away from.
		// Always returns false if used with an uninitialized line
		bool IsInside(const Vector2<T>& aPosition) const;
		// Returns the direction of the line, which is (normal.y, -normal.x).
		// If saved as member variable return as const reference
		Vector2<T> GetDirection() const;
		// Returns the normal of the line, which is (-direction.y, direction.x).
		// If saved as member variable return as const reference
		Vector2<T> GetNormal() const;
	private:
		Vector2<T> myNormal;
		Vector2<T> myPoint;
	};
	template<typename T>
	inline Line<T>::Line() :myNormal(), myPoint()
	{
	}
	template<typename T>
	inline Line<T>::Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		InitWith2Points(aPoint0, aPoint1);
	}
	template<typename T>
	inline void Line<T>::InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		Vector2<T> direction = aPoint1 - aPoint0;
		myNormal = Vector2<T>(-direction.y, direction.x).GetNormalized();
		myPoint = aPoint0;
	}
	template<typename T>
	inline void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
	{
		myNormal = Vector2<T>(-aDirection.y, aDirection.x).GetNormalized();
		myPoint = aPoint;
	}
	template<typename T>
	inline void Line<T>::InitWithPointAndNormal(const Vector2<T>& aPoint, const Vector2<T>& aNormal)
	{
		myNormal = aNormal.GetNormalized();
		myPoint = aPoint;
	}

	template<typename T>
	inline bool Line<T>::IsInside(const Vector2<T>& aPosition) const
	{
		if (myNormal == Vector2<T>::zero) return false;
		return GetNormal().Dot(aPosition - myPoint) <= 0;
	}
	template<typename T>
	inline Vector2<T> Line<T>::GetDirection() const
	{
		return {myNormal.y, -myNormal.x};
	}

	template<typename T>
	inline Vector2<T> Line<T>::GetNormal() const
	{
		return myNormal;
	}
}