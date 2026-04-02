#pragma once
#include "Plane.hpp"
#include "Sphere.hpp"
#include "AABB3D.hpp"
#include "Ray.hpp"


namespace CommonUtilities 
{
	
	// If the ray is parallel to the plane, aOutIntersectionPoint remains unchanged. If
	// the ray is in the plane, true is returned, if not, false is returned. If the ray
	// isn't parallel to the plane and hits, the intersection point is stored in
	// aOutIntersectionPoint and true returned otherwise false is returned and 
	// outIntersectionPoint is unchanged.
	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& outIntersectionPoint);
	// If no collision, aOutIntersectionPoint remains unchanged. 
	// If The sphere overlaps the AABB true is returned, if not, false is returned.
	// The point on the AABB closest to the sphere centre is saved in 
	// aOutIntersectionPoint.
	// A sphere touching the aabb is considered overlapping.
	template<typename T>
	bool IntersectionSphereAABB(const Sphere<T>& aSphere, const AABB3D<T>& aAABB3D, Vector3<T>& outIntersectionPoint);
	// If the ray intersects the AABB, true is returned, if not, false is returned.
	// A ray in one of the AABB's sides is counted as intersecting it.
	template<typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay);
	// If the ray intersects the sphere, true is returned, if not, false is returned.
	// A ray intersecting the surface of the sphere is considered as intersecting it.
	template<typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay);


	//--- IMPLEMENTATIONS ---

	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& outIntersectionPoint)
	{

		//if dot is zero we are paralell to plane
		const T parallell = aPlane.GetNormal().Dot(aRay.GetDirection());
		
		if (std::abs(parallell) < Math<T>::Epsilon)
		{
			const T inPlane = aPlane.GetNormal().Dot(aRay.GetOrigin() - aPlane.GetPoint());
			return std::abs(inPlane) < Math<T>::Epsilon;
		}
		const T d = aPlane.GetNormal().Dot(aPlane.GetPoint());
		//(o+dir*t).n = t => t = (d - n.o)/n.dir 
		const T t = (d - aPlane.GetNormal().Dot(aRay.GetOrigin())) / parallell;
		if (t >= 0) 
		{
			outIntersectionPoint = aRay.GetDirection() * t + aRay.GetOrigin();
			return true;
		}
		

		return false;
	}

	template<typename T>
	bool IntersectionSphereAABB(const Sphere<T>& aSphere, const AABB3D<T>& aAABB3D, Vector3<T>& outIntersectionPoint)
	{

		const Vector3<T> center = aSphere.GetCenter();
		const Vector3<T> closestPoint = aAABB3D.ClosestPoint(center);

		const T radius = aSphere.GetRadius();
		if ((closestPoint - center).LengthSqr() <= radius * radius) {
			outIntersectionPoint = closestPoint;
			return true;
		}

		return false;
	}

	template<typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay)
	{

		Vector3<T> rayOrigin = aRay.GetOrigin();
		Vector3<T> rayDir= aRay.GetDirection();
		Vector3<T> min = aAABB.GetMin();
		Vector3<T> max = aAABB.GetMax();


		bool inside = true;
		T xt;
		T xn;
		if (rayOrigin.x < min.x) {						// we are to the left of box
			xt = min.x - rayOrigin.x;					// distance to box from origin
			if (rayDir.x < 0) return false;				// ray heading away from box means no intersect possible
			xt /= rayDir.x;								// scale t, "normalize" to be the length in relation to the vector in this axis
			inside = false;								// we are not inside the box
			xn = T(-1.0);								// set the normal direction
		}
		else if (rayOrigin.x > max.x) {					//we are to the right of the box
			xt = max.x - rayOrigin.x;
			if (rayDir.x > 0) return false;
			xt /= rayDir.x;
			inside = false;
			xn = T(1.0);
		}
		else {											//we are in a slab, we cannot hit the box on this plane (yz)
			xt = T(-1.0);								// set t negative to remove from consideration	
		}

		T yt;
		T yn;
		if (rayOrigin.y < min.y) {
			yt = min.y - rayOrigin.y;
			if (rayDir.y < 0) return false;
			yt /= rayDir.y;
			inside = false;
			yn = T(-1.0);
		}
		else if (rayOrigin.y > max.y) {
			yt = max.y - rayOrigin.y;
			if (rayDir.y > 0) return false;
			yt /= rayDir.y;
			inside = false;
			yn = T(1.0);
		}
		else {
			yt = T(-1.0);
		}

		T zt;
		T zn;
		if (rayOrigin.z < min.z) {
			zt = min.z - rayOrigin.z;
			if (rayDir.z < 0) return false;
			zt /= rayDir.z;
			inside = false;
			zn = T(-1.0);
		}
		else if (rayOrigin.z > max.z) {
			zt = max.z - rayOrigin.z;
			if (rayDir.z > 0) return false;
			zt /= rayDir.z;
			inside = false;
			zn = T(1.0);
		}
		else {
			zt = T(-1.0);
		}

		if (inside) {			
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
				T y = rayOrigin.y + rayDir.y * t;
				if (y < min.y || y > max.y) return false;
				T z = rayOrigin.z + rayDir.z * t;
				if (z < min.z || z > max.z) return false;

			} 
			break;
			case 1: // intersect with xz plane
			{
				T x = rayOrigin.x + rayDir.x * t;
				if (x < min.x || x > max.x) return false;
				T z = rayOrigin.z + rayDir.z * t;
				if (z < min.z || z > max.z) return false;

			} 
			break;
			case 2: // intersect with xy plane
			{
				T x = rayOrigin.x + rayDir.x * t;
				if (x < min.x || x > max.x) return false;
				T y = rayOrigin.y + rayDir.y * t;
				if (y < min.y || y > max.y) return false;
			} 
			break;
		}


		return true;
	}

	template<typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay)
	{

		const Vector3<T> c = aSphere.GetCenter();
		const Vector3<T> p0 = aRay.GetOrigin();
		const Vector3<T> d = aRay.GetDirection();
		const Vector3<T> e = c - p0;
		const T a = e.Dot(d);
		const T r = aSphere.GetRadius();
		const T e2 = e.Dot(e);
		const T root = (r * r) - e2 + (a * a);
		if (root < 0)
		{
			return false;
		}

		//intersection behind spehere
		//I dont need sq_rooting since I dont look for an intersect point/distance...
		if (a*root - root < 0) 
		{
			return false;
		}

		return true;
	}


	
}