#pragma once
#include "Vector3.hpp"

namespace CommonUtilities {
	template<typename T>
	class AABB3D
	{
	public:
		// Default constructor: there is no AABB, both min and max points are the zero vector.
		AABB3D();
		// Constructor taking the positions of the minimum and maximum corners.
		AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax);
		// Init the AABB with the positions of the minimum and maximum corners, same as
		// the constructor above.
		void InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax);
		// Returns the min point of the AABB.
		const Vector3<T>& GetMin() const;
		// Returns the max point of the AABB.
		const Vector3<T>& GetMax() const;
		bool IsInside(const Vector3<T>& aPosition) const;
		//// Returns the center point of the AABB.
		//const Vector3<T>& GetCenter() const;
		//// Returns the extents of the AABB.
		//const Vector3<T>& GetExtents() const;
		Vector3<T> ClosestPoint(const Vector3<T>& aPosition) const;
	private:
		Vector3<T> myMin;
		Vector3<T> myMax;
	};


	template<typename T>
	AABB3D<T>::AABB3D()
	{
	}
	template<typename T>
	inline AABB3D<T>::AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax):myMin(aMin),myMax(aMax)
	{

	}
	template<typename T>
	inline void AABB3D<T>::InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}
	template<typename T>
	inline const Vector3<T>& AABB3D<T>::GetMin() const
	{
		return myMin;
	}
	template<typename T>
	inline const Vector3<T>& AABB3D<T>::GetMax() const
	{
		return myMax;
	}

	template<typename T>
	bool AABB3D<T>::IsInside(const Vector3<T>& aPosition) const
	{
		if (aPosition.x > myMax.x || aPosition.x < myMin.x) return false;
		if (aPosition.y > myMax.y || aPosition.y < myMin.y) return false;
		if (aPosition.z > myMax.z || aPosition.z < myMin.z) return false;
		return true;
	}

	template<typename T>
	Vector3<T> AABB3D<T>::ClosestPoint(const Vector3<T>& aPosition) const
	{
		T x = Math<T>::Clamp(aPosition.x, myMin.x, myMax.x);
		T y = Math<T>::Clamp(aPosition.y, myMin.y, myMax.y);
		T z = Math<T>::Clamp(aPosition.z, myMin.z, myMax.z);
		return { x,y,z };
	}
}



