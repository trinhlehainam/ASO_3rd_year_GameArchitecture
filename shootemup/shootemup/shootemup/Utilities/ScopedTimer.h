#pragma once
#include <chrono>

class ScopedTimer
{
	using ClockType = std::chrono::steady_clock;
public:
	ScopedTimer(const char* func_name);
	~ScopedTimer();
private:
	ScopedTimer(const ScopedTimer&) = delete;
	ScopedTimer(const ScopedTimer&&) = delete;
	void operator = (const ScopedTimer&) = delete;
	void operator = (ScopedTimer&&) = delete;

	const char* m_funcName;
	const ClockType::time_point m_start;
};

