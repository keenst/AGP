#pragma once
#include "Vector.hpp"
#include "AABB3D.hpp"

namespace CommonUtilities {

	template<typename T>
	struct RaycastHit {
		Vector3<T> point;
		Vector3<T> normal;
		T distance;
	};

	//aRayDir is the direction of the ray and needs to be normalized before calling this
	template<typename T>
	bool RaycastVsAABB(const AABB3D<T>& aAABB, Vector3<T> aRayOrigin, const Vector3<T>& aRayDir, RaycastHit<T>& outRaycastHit, const T& aDistance = std::numeric_limits<T>::max())
	{
		//static_assert(std::is_floating_point<T>::value, "RaycastVsAABB should be floating point type... What are you doing?");
		const Vector3<T> min = aAABB.GetMin();
		const Vector3<T> max = aAABB.GetMax();
		const Vector3<T> rayDelta = aRayDir * aDistance;

		bool inside = true;
		T xt;
		T xn;
		if (aRayOrigin.x < min.x) {
			xt = min.x - aRayOrigin.x;
			if (xt > rayDelta.x) return false;
			xt /= rayDelta.x;
			inside = false;
			xn = T(-1.0);
		}
		else if (aRayOrigin.x > max.x) {
			xt = max.x - aRayOrigin.x;
			if (xt < rayDelta.x) return false;
			xt /= rayDelta.x;
			inside = false;
			xn = T(1.0);
		}
		else {
			xt = T(-1.0);
		}

		T yt;
		T yn;
		if (aRayOrigin.y < min.y) {
			yt = min.y - aRayOrigin.y;
			if (yt > rayDelta.y) return false;
			yt /= rayDelta.y;
			inside = false;
			yn = T(-1.0);
		}
		else if (aRayOrigin.y > max.y) {
			yt = max.y - aRayOrigin.y;
			if (yt < rayDelta.y) return false;
			yt /= rayDelta.y;
			inside = false;
			yn = T(1.0);
		}
		else {
			yt = T(-1.0);
		}

		T zt;
		T zn;
		if (aRayOrigin.z < min.z) {
			zt = min.z - aRayOrigin.z;
			if (zt > rayDelta.z) return false;
			zt /= rayDelta.z;
			inside = false;
			zn = T(-1.0);
		}
		else if (aRayOrigin.z > max.z) {
			zt = max.z - aRayOrigin.z;
			if (zt < rayDelta.z) return false;
			zt /= rayDelta.z;
			inside = false;
			zn = T(1.0);
		}
		else {
			zt = T(-1.0);
		}

		// Ray origin inside box?
		if (inside) {

			outRaycastHit.point = aRayOrigin;
			outRaycastHit.normal = -aRayDir;
			outRaycastHit.distance = T(0);
			return true;
		}

		// Select farthest plane - this is the plane of intersection.
		int which = 0;
		T t = xt;
		if (yt > t) {
			which = 1;
			t = yt;
		}
		if (zt > t) {
			which = 2;
			t = zt;
		}

		switch (which) {
			case 0: // intersect with yz plane
			{
				T y = aRayOrigin.y + rayDelta.y * t;
				if (y < min.y || y > max.y) return false;
				T z = aRayOrigin.z + rayDelta.z * t;
				if (z < min.z || z > max.z) return false;


				outRaycastHit.point = aRayOrigin + rayDelta * t;
				outRaycastHit.normal = { xn, 0, 0 };
				outRaycastHit.distance = t * aDistance;
				return true;
			}
			case 1: // intersect with xz plane
			{
				T x = aRayOrigin.x + rayDelta.x * t;
				if (x < min.x || x > max.x) return false;
				T z = aRayOrigin.z + rayDelta.z * t;
				if (z < min.z || z > max.z) return false;
				outRaycastHit.point = aRayOrigin + rayDelta * t;
				outRaycastHit.normal = { 0, yn, 0 };
				outRaycastHit.distance = t * aDistance;
				return true;
			}
			case 2: // intersect with xy plane
			{
				T x = aRayOrigin.x + rayDelta.x * t;
				if (x < min.x || x > max.x) return false;
				T y = aRayOrigin.y + rayDelta.y * t;
				if (y < min.y || y > max.y) return false;
				outRaycastHit.point = aRayOrigin + rayDelta * t;
				outRaycastHit.normal = { 0, 0, zn };
				outRaycastHit.distance = t * aDistance;
				return true;
			}
		}

		return false;
		
	}
}