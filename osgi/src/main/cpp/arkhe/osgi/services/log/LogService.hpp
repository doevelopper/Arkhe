#ifndef ARKHE_OSGI_SERVICES_LOGSERVICE_HPP
#define ARKHE_OSGI_SERVICES_LOGSERVICE_HPP

#include <QString>
#include <exception>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceReference.hpp>
/*!
 * @brief 
 * 
 */
namespace osgi
{
	namespace svc
	{
		namespace log
		{
			class ARKHE_CORE_PLUGIN_FW_EXPORT LogService
			{

			public:
				LogService();
				virtual ~LogService();
				
				virtual void log(int level, const QString& message, const std::exception* exception = 0,
								const char* file = 0, const char* function = 0, int line = -1) = 0;
							
				virtual void log(const osgi::core::ServiceReference& sr, int level, const QString& message,
								const std::exception* exception = 0, const char* file = 0, const char* function = 0, int line = -1) = 0;

				virtual int getLogLevel() const = 0;
			protected:

			private:
				static const int LOG_FATAL;
				static const int LOG_CRITICAL;
				static const int LOG_ERROR;
				static const int LOG_WARNING;
				static const int LOG_INFO;
				static const int LOG_DEBUG;
				static const int LOG_TRACE;
				static const int LOG_OFF;
			};		
		}
	}
}
Q_DECLARE_INTERFACE(osgi::svc::log::LogService, "000.levitics.arkhe.service.log.LogService")
#endif
