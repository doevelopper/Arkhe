#ifndef ARKHE_OSGI_HIGHPRECISIONTIMER_HPP
#define ARKHE_OSGI_HIGHPRECISIONTIMER_HPP

#include <qglobal.h>

#undef USE_TIMER_FALLBACK

#ifdef Q_OS_MAC
	#include <mach/mach_time.h>
#elif defined(Q_OS_UNIX)
	#include <time.h>
	#include <unistd.h>
	#ifndef _POSIX_MONOTONIC_CLOCK
		#warning Monotonic clock support missing on this POSIX platform
		#define USE_TIMER_FALLBACK
	#endif
#elif defined(Q_OS_WIN)
	#include <windows.h>
#else
	#define USE_TIMER_FALLBACK
#endif

#ifdef USE_TIMER_FALLBACK
	#warning ctkHighPrecisionTimer is using the slower QTime fallback
	#include <QTime>
#endif


#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractObjectFactory.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class HighPrecisionTimer
		{
		public:

			explicit HighPrecisionTimer();
			virtual ~HighPrecisionTimer();

			void start();
			qint64 elapsedMilli();
			qint64 elapsedMicro();
		protected:

		private:

			HighPrecisionTimer(const HighPrecisionTimer &);  /// Not implemented
			void operator=(const HighPrecisionTimer&); /// Not implemented
			
			// only used on MacOS, but needs to be defined in the .cpp file
			static double timeConvert;

#ifdef USE_TIMER_FALLBACK
			QTime startTime;
#elif defined(Q_OS_MAC)
			quint64 startTime;
#elif defined(Q_OS_UNIX)
			timespec startTime;
#elif defined(Q_OS_WIN)
			LARGE_INTEGER timerFrequency;
			LARGE_INTEGER startTime;
#endif
		};
		
	}
		
}
#endif
