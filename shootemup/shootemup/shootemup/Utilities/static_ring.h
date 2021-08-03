#pragma once
#include <array>
#include <cassert>

#include "ring_iterator.h"

template<typename T, size_t size>
class static_ring
{
public:
	using iterator = ring_iterator<T, size>;

	static_ring();
	~static_ring() {}

	void insert(const T& value);
	
	void set_head_to_tail_loop() { m_isReversedLoop = true; }
	void set_tail_to_head_loop() { m_isReversedLoop = false; }

#pragma region get methods
	T& operator[](size_t index) { return m_data[index]; }

	size_t get_head_index() const { return m_head; }
	size_t get_tail_index() const { return m_tail; }

	size_t get_size() const { return m_data.size(); }

	T* data() { return m_data.data(); }
#pragma endregion

	iterator begin();
	iterator end() { return iterator(); }
private:
	size_t m_head;
	size_t m_tail;
	std::array<T, size> m_data;
	bool m_isReversedLoop;
};

template<typename T, size_t size>
inline static_ring<T, size>::static_ring() :m_head(size - 1), m_tail((m_head + 1) % size), m_data{}, m_isReversedLoop(false) {}

template<typename T, size_t size>
inline void static_ring<T, size>::insert(const T& value)
{
	m_head = (m_head + 1) % size;
	m_tail = (m_tail + 1) % size;
	m_data[m_head] = value;
}

template<typename T, size_t size>
inline ring_iterator<T, size> static_ring<T, size>::begin()
{
	return ring_iterator<T, size>(m_data.data(), m_isReversedLoop ? m_head : m_tail, m_isReversedLoop);
}
