#include "vec2.h"

#include <cmath>
#include <cassert>
#include <algorithm>

#include "MathHelper.h"

template<typename T>
vec2<T>::vec2():x(0),y(0)
{
}


template<typename T>
vec2<T>::vec2(T x, T y):x(x),y(y)
{
}

template<typename T>
vec2<T>::vec2(const vec2& other)
{
	x = other.x;
	y = other.y;
}

template<typename T>
vec2<T>::~vec2() = default;

template<typename T>
vec2<T>& vec2<T>::operator=(const vec2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator+=(const vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator-=(const vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator*=(int scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator/=(int scalar)
{
	assert(scalar != 0);
	x /= scalar;
	y /= scalar;
	return *this;
}

template<typename T>
T& vec2<T>::operator[](unsigned int i)
{
	assert(i >= 0 && i < 2);
	auto ret = reinterpret_cast<T*>(this);
	return *(ret + i);
}

template<typename T>
vec2<T> vec2<T>::operator-() const
{
	return vec2(-x, -y);
}

template<typename T>
vec2<T> vec2<T>::operator+() const
{
	return *this;
}

template<typename T>
vec2<T> operator+(const vec2<T>& a, const vec2<T>& b)
{
	return vec2<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
vec2<T> operator-(const vec2<T>& a, const vec2<T>& b)
{
	return vec2<T>(a.x - b.x, a.y - b.y);
}

template<typename T>
vec2<T> operator*(const vec2<T>& a, T scalar)
{
	return vec2<T>(a.x * scalar, a.y * scalar);
}

template<typename T>
vec2<T> operator*(T scalar, const vec2<T>& a)
{
	return vec2<T>(a.x * scalar, a.y * scalar);
}

template<typename T>
T operator*(const vec2<T> a, const vec2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}

template<typename T>
vec2<T> operator/(const vec2<T>& a, T scalar)
{
	assert(scalar != 0);
	return vec2<T>(a.x / scalar, a.y / scalar);
}

template<typename T>
vec2<T> operator%(const vec2<T>& a, int scalar)
{
	assert(scalar != 0);
	return vec2<T>(static_cast<T>(static_cast<int>(a.x) % scalar), static_cast<T>(static_cast<int>(a.y) % scalar));
}

template<typename T>
bool operator==(const vec2<T>& a, T value)
{
	return a.x == value && a.y == value;
}

template<typename T>
bool operator==(const vec2<T>& a, const vec2<T>& b)
{
	return a.x == b.x && a.y == b.y;
}

template<typename T>
bool operator!=(const vec2<T>& a, const vec2<T>& b)
{
	return a.x != b.x || a.y != b.y;
}

template<typename T>
bool operator>=(const vec2<T>& a, const vec2<T>& b)
{
	return a.x >= b.x && a.y >= b.y;
}

template<typename T>
bool operator>(const vec2<T>& a, const vec2<T>& b)
{
	return a.x > b.x && a.y > b.y;
}

template<typename T>
bool operator<=(const vec2<T>& a, const vec2<T>& b)
{
	return a.x <= b.x && a.y <= b.y;
}

template<typename T>
bool operator<(const vec2<T>& a, const vec2<T>& b)
{
	return a.x < b.x && a.y < b.y;
}

template<typename T>
T dot(const vec2<T>& a, const vec2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}

template<typename T>
T length(const vec2<T>& v)
{
	return static_cast<T>(std::sqrt(v.x * v.x + v.y * v.y));
}

template<typename T>
vec2<T> unitVec(const vec2<T>& v)
{
	auto l = length(v);
	assert(!MathHelper::isEqual<T>(l,0));
	return v / l;
}

template<typename T>
vec2<T> invertedVec(const vec2<T>& v)
{
	assert(v.x != static_cast<T>(0));
	assert(v.y != static_cast<T>(0));
	return vec2<T>{1.0f / v.x, 1.0f / v.y};
}

template<typename T>
vec2<T> reflectionVec(const vec2<T>& i, const vec2<T>& n)
{
	return i - static_cast<T>(2) * (n * i) * n;
}

template<typename T>
vec2<T> projectVec(const vec2<T>& v, const vec2<T>& onto)
{
	return onto * (dot(v, onto) / dot(onto, onto));
}

template<typename T>
vec2<T> orthogonalVec(const vec2<T>& v)
{
	return vec2<T>{-v.y, v.x};
}

template<typename T>
bool isParallelVec(const vec2<T>& a, const vec2<T>& b)
{
	return dot(orthogonalVec(a), b) == 0;
}

template<typename T>
vec2<T> clampVec(const vec2<T>& value, const vec2<T>& min, const vec2<T>& max)
{
	auto clamped_x = MathHelper::clamp(value.x, min.x, max.x);
	auto clamped_y = MathHelper::clamp(value.y, min.y, max.y);
	return vec2<T>{clamped_x, clamped_y};
}

#pragma region Specialization
template <>
vec2u vec2u::operator - () const
{
	assert(0);			// Unsgined number can't be negative
	return vec2u(x, y);
}

template <>
bool operator == (const vec2f& a, float value)
{
	return MathHelper::isEqual(a.x,value) && MathHelper::isEqual(a.y, value);
}

template <> 
bool operator == (const vec2f& a, const vec2f& b)
{
	auto vec_dif = a - b;
	return vec_dif == MathHelper::kBiasF;
}

template <>
bool isParallelVec(const vec2f& a, const vec2f& b)
{
	return MathHelper::isEqual(dot(orthogonalVec(a), b), 0.0f);
}
#pragma endregion


#define InstantiateFuncTemplate(type)\
template vec2<type> operator + (const vec2<type>& a, const vec2<type>& b);		\
template vec2<type> operator - (const vec2<type>& a, const vec2<type>& b);		\
template vec2<type> operator * (const vec2<type>& a, type scalar);				\
template vec2<type> operator * (type scalar, const vec2<type>& a);				\
template vec2<type> operator / (const vec2<type>& a, type scalar);				\
template vec2<type> operator % (const vec2<type>& a, int scalar);				\
																				\
template bool operator == (const vec2<type>& a, const vec2<type>& b);			\
template bool operator != (const vec2<type>& a, const vec2<type>& b);			\
template bool operator >= (const vec2<type>& a, const vec2<type>& b);			\
template bool operator >  (const vec2<type>& a, const vec2<type>& b);			\
template bool operator <= (const vec2<type>& a, const vec2<type>& b);			\
template bool operator <  (const vec2<type>& a, const vec2<type>& b);			\

#pragma region InstantiateFuncTemplate

template vec2<int>;
template vec2<unsigned int>;
template vec2<float>;
template vec2<double>;

InstantiateFuncTemplate(int);
InstantiateFuncTemplate(unsigned int);
InstantiateFuncTemplate(float);
InstantiateFuncTemplate(double);

#pragma region float
template vec2f unitVec(const vec2f&);
template vec2f invertedVec(const vec2f&);
template float dot(const vec2f& a, const vec2f& b);
template vec2f reflectionVec(const vec2f& i, const vec2f& n);
template vec2f projectVec(const vec2f& v, const vec2f& n);
template vec2f orthogonalVec(const vec2f& v);
template vec2f clampVec(const vec2f& value, const vec2f& min, const vec2f& max);
#pragma endregion

#pragma region double
template vec2d unitVec(const vec2d&);
template vec2d invertedVec(const vec2d&);
template double dot(const vec2d& a, const vec2d& b);
template vec2d reflectionVec(const vec2d& i, const vec2d& n);
template vec2d projectVec(const vec2d& vi, const vec2d& onto);
template vec2d orthogonalVec(const vec2d& v);
template vec2d clampVec(const vec2d& value, const vec2d& min, const vec2d& max);
#pragma endregion

#pragma endregion

