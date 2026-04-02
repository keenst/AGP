#pragma once
#include <cmath>
#include <type_traits>

#undef min
#undef max


template<typename T>
class Math;
template<typename T>
static constexpr std::enable_if_t<std::is_floating_point<T>::value, bool> _Approx(T a, T b)
{
	return (a < b + Math<T>::Epsilon) && (a > b - Math<T>::Epsilon);
}

template<typename T>
static constexpr std::enable_if_t<!std::is_floating_point<T>::value, bool> _Approx(T a, T b)
{
	return a == b;
}

template<typename T>
class Math
{
public:




	//constexpr static float Epsilon = static_cast<T>(0.00001);
	static const T Epsilon;

	constexpr static T Pi = static_cast<T>(3.14159265359);
	constexpr static T TwoPi = Pi * static_cast<T>(2.0);
	constexpr static T HalfPi = Pi / static_cast<T>(2.0);
	constexpr static T DegToRad = Pi / static_cast<T>(180.0);
	constexpr static T RadToDeg = static_cast<T>(180.0) / Pi;

	/// <summary>
/// Safe way to compare floats, will not allow NaNs to slip through!
/// </summary>
/// <param name="value">number to check</param>
/// <param name="min">(inclusive)</param>
/// <param name="max">(inclusive)</param>
/// <returns>true if value is in range [min...max]</returns>
	static constexpr bool NumberInRange(T value, T min, T max)
	{
		if (value >= min && value <= max)
		{
			return true;
		}
		return false;
	}

	static constexpr T Sqrt(T aValue)
	{
		return std::sqrt(aValue);
	}

	static constexpr T Sin(T aAngleInRadians)
	{
		return std::sin(aAngleInRadians);
	}

	static constexpr T Cos(T aAngleInRadians)
	{
		return std::cos(aAngleInRadians);
	}

	static constexpr T Tan(T aAngleInRadians)
	{
		return std::tan(aAngleInRadians);
	}

	static constexpr T Atan(T aAngleInRadians)
	{
		return std::atan(aAngleInRadians);
	}

	static constexpr T Atan2(T y, T x)
	{
		return std::atan2(y,x);
	}

	static constexpr T Log2(T aValue)
	{
		return std::log2(aValue);
	}

	static constexpr T Pow(T aBase, T aExponent)
	{
		return std::pow(aBase, aExponent);
	}

	template<typename TValue>
	static constexpr T Floor(TValue aValue)
	{
		return static_cast<T>(std::floor(aValue));
	}

	template<typename TValue>
	static constexpr T Ceil(TValue aValue)
	{

		return static_cast<T>(std::ceil(aValue));
		//long long intPart = static_cast<long long>(aValue);
		//if (aValue == static_cast<T>(intPart))
		//{
		//	return static_cast<T>(aValue);
		//}

		//if (0 < aValue)
		//{
		//	return static_cast<T>(intPart+1);
		//}

		//return static_cast<T>(intPart);
	}

	static constexpr const T& Abs(const T& aValue)
	{
		return std::abs(aValue);
	}



	static constexpr T Max(T a, T b)
	{
		return std::max(a, b);
	}

	static constexpr T Min(T a, T b)
	{
		return std::min(a, b);
	}

	static constexpr T Clamp(T value, T min, T max)
	{
		return std::min(max, std::max(min, value));
	}

	static constexpr T Clamp01(T value)
	{
		return Clamp(value, static_cast<T>(0.0), static_cast<T>(1.0));
	}

	template<typename TValue>
	static constexpr TValue Lerp(TValue from, TValue to, T t)
	{
		return from + (to - from) * Clamp01(t);
	}

	template<typename TValue>
	static constexpr T InverseLerp(TValue from, TValue to, T t)
	{
		return Clamp01((t - from) / (to - from));
	}

	template<typename TValue>
	static constexpr T LerpUnclamped(TValue from, TValue to, T t)
	{
		return from + (to - from) * t;
	}

	template<typename TValue>
	static constexpr T InverseLerpUnclamped(TValue from, TValue to, T t)
	{
		return (t - from) / (to - from);
	}

	template<typename TValue>
	static constexpr TValue Remap(TValue originalFrom, TValue originalTo, TValue targetFrom, TValue targetTo, T t)
	{
		TValue rel = InverseLerp(originalFrom, originalTo, t);
		return Lerp(targetFrom, targetTo, rel);
	}

	static constexpr bool Approximately(T a, T b, T epsilon = Epsilon)
	{
		return !(a > (b + epsilon)) && !(a < (b - epsilon));
	}

	static constexpr bool IsZero(T a, T epsilon = Epsilon)
	{
		return !(a < -epsilon) && !(a > epsilon);
	}
	static constexpr bool Approx(T a, T b)
	{
		return _Approx(a, b);
	}


	//static constexpr typename std::enable_if_t<std::is_floating_point<T>::value, bool> 
	//	Approximately(T a, T b, T epsilon = Epsilon)
	//{
	//	return (a < b + epsilon) && (a > b - epsilon);
	//}

	//static constexpr typename std::enable_if_t<std::is_floating_point<T>::value, bool> 
	//	IsZero(T a, T epsilon = Epsilon)
	//{
	//	return (a < epsilon) && (a > -epsilon);
	//}

	//static constexpr typename std::enable_if_t<std::is_integral<T>::value, bool>
	//	Approximately(T a, T b, T epsilon = Epsilon)
	//{
	//	epsilon;
	//	return a==b;
	//}

	//static constexpr typename std::enable_if_t<std::is_integral<T>::value, bool>
	//	IsZero(T a, T epsilon = Epsilon)
	//{
	//	epsilon;
	//	return a==0;
	//}

	static constexpr const T& _Abs(const T& aValue)
	{
		return (aValue < 0) ? -aValue : aValue;
	}


};

using Mathf = Math<float>;
using Mathd = Math<double>;

constexpr float Math<float>::Epsilon = 0.000001f;
constexpr double Math<double>::Epsilon = 0.0000001;

template<typename T>
const T Math<T>::Epsilon = static_cast<T>(0.000001);



