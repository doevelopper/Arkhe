#include <arkhe/osgi/core/HighPrecisionTimer.hpp>

double osgi::core::HighPrecisionTimer::timeConvert = 0.0;

// osgi::core::HighPrecisionTimer::HighPrecisionTimer()
// {
	
// }

osgi::core::HighPrecisionTimer::~HighPrecisionTimer()
{
	
}

#ifdef USE_TIMER_FALLBACK

inline osgi::core::HighPrecisionTimer::HighPrecisionTimer()
  : startTime(QTime::currentTime())
{
}

inline void osgi::core::HighPrecisionTimer::start()
{
  startTime = QTime::currentTime();
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMilli()
{
  return startTime.elapsed();
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMicro()
{
  return startTime.elapsed() * 1000;
}


#elif defined(Q_OS_MAC)

inline osgi::core::HighPrecisionTimer::ctkHighPrecisionTimer()
: startTime(0)
{
	if (timeConvert == 0)
	{
		mach_timebase_info_data_t timeBase;
		mach_timebase_info(&timeBase);
		timeConvert = static_cast<double>(timeBase.numer) / static_cast<double>(timeBase.denom) / 1000.0;
	}
}

inline void osgi::core::HighPrecisionTimer::start()
{
	startTime = mach_absolute_time();
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMilli()
{
	quint64 current = mach_absolute_time();
	return static_cast<double>(current - startTime) * timeConvert / 1000.0;
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMicro()
{
	quint64 current = mach_absolute_time();
	return static_cast<double>(current - startTime) * timeConvert;
}

#elif defined(Q_OS_UNIX)

inline osgi::core::HighPrecisionTimer::ctkHighPrecisionTimer()
{
	startTime.tv_nsec = 0;
	startTime.tv_sec = 0;
}

inline void osgi::core::HighPrecisionTimer::start()
{
	clock_gettime(CLOCK_MONOTONIC, &startTime);
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMilli()
{
	timespec current;
	clock_gettime(CLOCK_MONOTONIC, &current);
	return (static_cast<qint64>(current.tv_sec)*1000 + current.tv_nsec/1000/1000) -
		(static_cast<qint64>(startTime.tv_sec)*1000 + startTime.tv_nsec/1000/1000);
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMicro()
{
	timespec current;
	clock_gettime(CLOCK_MONOTONIC, &current);
	return (static_cast<qint64>(current.tv_sec)*1000*1000 + current.tv_nsec/1000) -
		(static_cast<qint64>(startTime.tv_sec)*1000*1000 + startTime.tv_nsec/1000);
}

#elif defined(Q_OS_WIN)

#include <arkhe/osgi/core/Exception.hpp>

inline osgi::core::HighPrecisionTimer::HighPrecisionTimer()
{
	//if (!QueryPerformanceFrequency(&timerFrequency))
		//throw RuntimeException("QueryPerformanceFrequency() failed");
}

inline void osgi::core::HighPrecisionTimer::start()
{
	//DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&startTime);
	//SetThreadAffinityMask(GetCurrentThread(), oldmask);
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMilli()
{
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);
		return (current.QuadPart - startTime.QuadPart) / (timerFrequency.QuadPart / 1000);
}

inline qint64 osgi::core::HighPrecisionTimer::elapsedMicro()
{
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);
	return (current.QuadPart - startTime.QuadPart) / (timerFrequency.QuadPart / (1000*1000));
}

#endif

