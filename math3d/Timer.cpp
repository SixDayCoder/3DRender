#include "Timer.h"

double Timer::DeltaTime()const
{
	return static_cast<double>(m_DeltaTime.count() / 1000000.0f);
}

double Timer::ElapsedTime()const
{
	microseconds tp = m_CurrentTime.time_since_epoch() - m_LastTime.time_since_epoch();
	return static_cast<double>(tp.count() / 1000000.0f);
}

double Timer::Frequency()const
{
	double delta = DeltaTime();
	if (delta <= 0.0)
	{
		return 0.0;
	}
	return 1.0 / delta;
}

void Timer::Stop()
{
	m_CurrentTime = std::chrono::time_point_cast<microseconds>(std::chrono::high_resolution_clock::now());
	m_LastTime = time_type();
	m_DeltaTime = milliseconds();
}

void Timer::Start()
{
	m_StartTime = std::chrono::time_point_cast<microseconds>(std::chrono::high_resolution_clock::now());
	m_LastTime = m_StartTime;
}

void Timer::Tick()
{
	m_LastTime = m_CurrentTime;
	m_CurrentTime = std::chrono::time_point_cast<microseconds>(std::chrono::high_resolution_clock::now());
	m_DeltaTime = m_CurrentTime.time_since_epoch() - m_LastTime.time_since_epoch();
}

Timer::Timer()
{
	CleanUp();
}

void Timer::CleanUp()
{
	m_StartTime = time_type();
	m_LastTime = time_type();
	m_CurrentTime = time_type();
	m_DeltaTime = milliseconds();
}