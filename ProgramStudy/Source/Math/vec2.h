#pragma once

template <typename T>
struct vec2
{
	vec2();
	vec2(T x, T y);
	vec2(const vec2& other);
	~vec2();

	T x, y;

#pragma region Assignment
	vec2& operator = (const vec2& other);
	vec2& operator += (const vec2& other);
	vec2& operator -= (const vec2& other);
	vec2& operator *= (int scalar);
	vec2& operator /= (int scalar);
#pragma endregion
	
#pragma region Unary
	T& operator [] (unsigned int i);
	vec2 operator - () const;
	vec2 operator + () const;
#pragma endregion

};

template<typename T> vec2<T> operator + (const vec2<T>& a, const vec2<T>& b);
template<typename T> vec2<T> operator - (const vec2<T>& a, const vec2<T>& b);
template<typename T> vec2<T> operator * (const vec2<T>& a, T scalar);
template<typename T> vec2<T> operator * (T scalar, const vec2<T>& a);
template<typename T> T operator * (const vec2<T> a, const vec2<T>& b);		// Dot product
template<typename T> vec2<T> operator / (const vec2<T>& a, T scalar);
template<typename T> vec2<T> operator % (const vec2<T>& a, int scalar);

template<typename T> bool operator == (const vec2<T>& a, T value);
template<typename T> bool operator == (const vec2<T>& a, const vec2<T>& b);
template<typename T> bool operator != (const vec2<T>& a, const vec2<T>& b);
template<typename T> bool operator >= (const vec2<T>& a, const vec2<T>& b);
template<typename T> bool operator >  (const vec2<T>& a, const vec2<T>& b);
template<typename T> bool operator <= (const vec2<T>& a, const vec2<T>& b);
template<typename T> bool operator <  (const vec2<T>& a, const vec2<T>& b);

template<typename T> T dot(const vec2<T>& a, const vec2<T>& b);
template<typename T> T length(const vec2<T>& v);
template<typename T> vec2<T> unitVec(const vec2<T>& v);
template<typename T> vec2<T> invertedVec(const vec2<T>& v);
template<typename T> vec2<T> reflectionVec(const vec2<T>& i, const vec2<T>& n);
template<typename T> vec2<T> projectVec(const vec2<T>& v, const vec2<T>& onto);
template<typename T> vec2<T> orthogonalVec(const vec2<T>& v);
template<typename T> bool isParallelVec(const vec2<T>& a, const vec2<T>& b);
template<typename T> vec2<T> clampVec(const vec2<T>& value, const vec2<T>& min, const vec2<T>& max);

using vec2i = vec2<int>;
using vec2u = vec2<unsigned int>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;

using position2i = vec2<int>;
using position2u = vec2<unsigned int>;
using position2f = vec2<float>;
using position2d = vec2<double>;