
#include <arkhe/osgi/Services/log/LogService.hpp>

const int osgi::svc::log::LogService::LOG_OFF = 0;
const int osgi::svc::log::LogService::LOG_TRACE = 1;
const int osgi::svc::log::LogService::LOG_DEBUG = 2;
const int osgi::svc::log::LogService::LOG_INFO = 3;
const int osgi::svc::log::LogService::LOG_WARNING = 4;
const int osgi::svc::log::LogService::LOG_ERROR = 5;
const int osgi::svc::log::LogService::LOG_FATAL = 6;
const int osgi::svc::log::LogService::LOG_CRITICAL = 7;
				
osgi::svc::log::LogService::LogService()
{
}

osgi::svc::log::LogService::~LogService()
{
}
