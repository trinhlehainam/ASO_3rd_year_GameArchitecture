#include "ScopedTimer.h"

ScopedTimer::ScopedTimer(const char* func_name) :m_funcName(std::move(func_name)), m_start(ClockType::now()) {}

ScopedTimer::~ScopedTimer()
{
	auto duration_ms = std::chrono::duration<float, std::chrono::milliseconds::period>(ClockType::now() - m_start).count();
}
