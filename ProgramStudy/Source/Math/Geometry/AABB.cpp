#include "AABB.h"

#include <algorithm>

template <typename T>
AABB<T>::AABB() = default;

template <typename T>
AABB<T>::AABB(const vec2<T>& pos, const vec2<T>& size) : Pos(pos), Size(size) {}

template <typename T>
void AABB<T>::operator=(const AABB<T>& other)
{
	Pos = other.Pos;
	Size = other.Size;
}

template <typename T>
void AABB<T>::operator=(AABB<T>&& other) noexcept
{
	std::swap(Pos, other.Pos);
	std::swap(Size, other.Size);
}

template <typename T>
AABB<T>::~AABB() = default;

#pragma region Instantiate
template AABB<int>;
template AABB<float>;
template AABB<double>;
#pragma endregion


