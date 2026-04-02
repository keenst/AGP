#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;
	Quaternion();
	Quaternion(float aX, float aY, float aZ, float aW);
	float SqMagnitude() const;
	float Magnitude() const;
	Quaternion Normalized() const;
	CommonUtilities::Matrix4x4<float> ToMatrix4x4() const;
	static Quaternion AngleAxis(float angle, const Vector3f& axis);
	static Quaternion FromEulerYXZ(float aX, float aY, float aZ);
	static Quaternion FromEulerXYZ(float aX, float aY, float aZ);
	static Quaternion Pow(const Quaternion& q, const float aExponent);
	static Quaternion Conjugate(const Quaternion& q);
	static Quaternion Inverse(const Quaternion& q);
	static float Dot(const Quaternion& a, const Quaternion& b);
	static Quaternion Slerp(const Quaternion& aFrom, const Quaternion& aTo, float t);
	Quaternion operator*(const Quaternion& aOther) const;
	Quaternion& operator*=(const Quaternion& aOther);

	static const Quaternion Identity;
};

Vector3f operator*(const Vector3f& aVector, const Quaternion& aQuaternion);