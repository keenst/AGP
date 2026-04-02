#include "Quaternion.h"
#include "Math.hpp"


Quaternion::Quaternion() : x(0), y(0), z(0), w(1)
{
}


Quaternion::Quaternion(float aX, float aY, float aZ, float aW) : x(aX), y(aY), z(aZ), w(aW)
{
}

float Quaternion::SqMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

float Quaternion::Magnitude() const
{
	return std::sqrt(SqMagnitude());
}

Quaternion Quaternion::Normalized() const
{
	float mag = 1.0f / Magnitude();
	return { x * mag, y * mag, z * mag, w * mag };
}

Quaternion Quaternion::AngleAxis(float angle, const Vector3f& axis)
{
	float halfAngle = angle * 0.5f;
	float s = std::sin(halfAngle);
	return { axis.x * s, axis.y * s, axis.z * s, std::cos(halfAngle) };
}

//check to see if this rotates right hadedly
Quaternion Quaternion::FromEulerYXZ(float aX, float aY, float aZ)
{

	const float cx = std::cos(aY / 2);
	const float sx = std::sin(aY / 2);
	const float cy = std::cos(aX / 2);
	const float sy = std::sin(aX / 2);
	const float cz = std::cos(aZ / 2);
	const float sz = std::sin(aZ / 2);
	//const float x = -cx * sy * cz - sx * cy * sz;
	//const float y = cx * sy * sz - sx * cy * cz;
	//const float z = sx * sy * cz - cx * cy * sz;
	//const float w = cx * cy * cz + sx * sy * sz;

	const float w = cx * cy * cz + sx * sy * sz;
	const float x = cx * sy * cz + sx * cy * sz;
	const float y = sx * cy * cz - cx * sy * sz;
	const float z = cx * cy * sz - sx * sy * cz;

	return {x,y,z,w};
}

Quaternion Quaternion::FromEulerXYZ(float aX, float aY, float aZ)
{

	const float cx = std::cos(aX / 2);
	const float sx = std::sin(aX / 2);
	const float cy = std::cos(aY / 2);
	const float sy = std::sin(aY / 2);
	const float cz = std::cos(aZ / 2);
	const float sz = std::sin(aZ / 2);
	//const float x = -cx * sy * cz - sx * cy * sz;
	//const float y = cx * sy * sz - sx * cy * cz;
	//const float z = sx * sy * cz - cx * cy * sz;
	//const float w = cx * cy * cz + sx * sy * sz;

	const float w =  cx * cy * cz + sx * sy * sz;
	const float x = -cx * sy * cz - sx * cy * sz;
	const float y =  cx * sy * sz - sx * cy * cz;
	const float z =  sx * sy * cz - cx * cy * sz;

	return { x,y,z,w };
}

Quaternion Quaternion::Pow(const Quaternion& q, const float aExponent)
{
	//GameMath book
	if (std::abs(q.w) < 1 - Mathf::Epsilon) {
		float alpha = std::acos(q.w);
		float newAlpha = alpha * aExponent;
		float w = std::cos(newAlpha);
		float s = std::sin(newAlpha) / std::sin(alpha);
		return
		{
			q.x * s,
			q.y * s,
			q.z * s,
			w
		};
	}

	return q;
}

Quaternion Quaternion::Conjugate(const Quaternion& q)
{
	return { -q.x, -q.y, -q.z, q.w };
}

Quaternion Quaternion::Inverse(const Quaternion& q)
{
	float m = 1.0f / q.Magnitude();
	return
	{
		-q.x * m,
		-q.y * m,
		-q.z * m,
		q.w  * m
	};
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Quaternion Quaternion::Slerp(const Quaternion& from, const Quaternion& to, float t)
{
	//GameMath book
	float x = to.x;
	float y = to.y;
	float z = to.z;
	float w = to.w;

	float cosOmega = Dot(from, to);
	if (cosOmega < 0.0f) {
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		cosOmega = -cosOmega;
	}

	// Check if they are very close together, to protect
	// against divide-by-zero
	float k0, k1;
	if (cosOmega > 1 - Mathf::Epsilon) {
		// Very close - just use linear interpolation
		k0 = 1.0f - t;
		k1 = t;
	}
	else {

		// Compute the sin of the angle using the
		// trig identity sin^2(omega) + cos^2(omega) = 1
		float sinOmega = std::sqrt(1.0f - cosOmega * cosOmega);

		// Compute the angle from its sine and cosine
		float omega = std::atan2(sinOmega, cosOmega);

		// Compute inverse of denominator, so we only have
		// to divide once
		float oneOverSinOmega = 1.0f / sinOmega;

		// Compute interpolation parameters
		k0 = std::sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = std::sin(t * omega) * oneOverSinOmega;
	}

	// Interpolate
	return
	{
		from.x * k0 + x * k1,
		from.y * k0 + y * k1,
		from.z * k0 + z * k1,
		from.w * k0 + w * k1
	};

}

CommonUtilities::Matrix4x4<float> Quaternion::ToMatrix4x4() const
{
	//from:
	//https://gamemath.com/book/orient.html#euler_angles_to_quaternion

	const float xx = 2.0f * x * x;
	const float yy = 2.0f * y * y;
	const float zz = 2.0f * z * z;
	const float xy = 2.0f * x * y;
	const float xz = 2.0f * x * z;
	const float yz = 2.0f * y * z;
	const float wx = 2.0f * w * x;
	const float wy = 2.0f * w * y;
	const float wz = 2.0f * w * z;

	//todo: transpose? we do a right handed matrix?? edit the transform from euler is right handed ?

	return CommonUtilities::Matrix4x4<float>(
		1.0f - yy - zz,		xy + wz,		xz - wy,		0.0f,
		xy - wz,			1.0f - xx - zz, yz + wx,		0.0f,
		xz + wy,			yz - wx,		1.0f - xx - yy, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	return
	{
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w,
		w * q.w - x * q.x - y * q.y - z * q.z
	};
}

Quaternion& Quaternion::operator*=(const Quaternion& aOther)
{
	*this = *this * aOther;
	return *this;
}

const Quaternion Quaternion::Identity = Quaternion(0, 0, 0, 1);

Vector3f operator*(const Vector3f& aVector, const Quaternion& aQuaternion)
{
	return Vector3f
	{
		aVector.x * (1 - 2 * (aQuaternion.y * aQuaternion.y + aQuaternion.z * aQuaternion.z)) +
		aVector.y * (2 * (aQuaternion.x * aQuaternion.y - aQuaternion.z * aQuaternion.w)) +
		aVector.z * (2 * (aQuaternion.x * aQuaternion.z + aQuaternion.y * aQuaternion.w)),
		aVector.x * (2 * (aQuaternion.x * aQuaternion.y + aQuaternion.z * aQuaternion.w)) +
		aVector.y * (1 - 2 * (aQuaternion.x * aQuaternion.x + aQuaternion.z * aQuaternion.z)) +
		aVector.z * (2 * (aQuaternion.y * aQuaternion.z - aQuaternion.x * aQuaternion.w)),
		aVector.x * (2 * (aQuaternion.x * aQuaternion.z - aQuaternion.y * aQuaternion.w)) +
		aVector.y * (2 * (aQuaternion.y * aQuaternion.z + aQuaternion.x * aQuaternion.w)) +
		aVector.z * (1 - 2 * (aQuaternion.x * aQuaternion.x + aQuaternion.y * aQuaternion.y))
	};
}

std::ostream& operator<<(std::ostream& aOutStream, const Quaternion& q)
{
	return aOutStream << "(x: " << q.x << ", y: " << q.y << ", z: " << q.z << ", w: " << q.w << ")";
}
