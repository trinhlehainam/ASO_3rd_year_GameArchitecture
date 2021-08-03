#include "ScopedTimer.h"

#include "../_debug/_DebugConOut.h"

ScopedTimer::ScopedTimer(const char* func_name) :m_funcName(std::move(func_name)), m_start(ClockType::now()) {}

ScopedTimer::~ScopedTimer()
{
	auto duration_ms = std::chrono::duration<float, std::chrono::milliseconds::period>(ClockType::now() - m_start).count();
	TRACE("%f ms ", duration_ms);
	TRACE(m_funcName);
	TRACE("\n");
}
