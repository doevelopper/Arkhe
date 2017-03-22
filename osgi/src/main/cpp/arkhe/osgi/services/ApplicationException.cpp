#include <arkhe/osgi/Services/ApplicationException.hpp>

const int ApplicationException::APPLICATION_LOCKED							= 0x01;
const int ApplicationException::APPLICATION_NOT_LAUNCHABLE 					= 0x02;
const int ApplicationException::APPLICATION_INTERNAL_ERROR 					= 0x03;
const int ApplicationException::APPLICATION_SCHEDULING_FAILED 				= 0x04;
const int ApplicationException::APPLICATION_DUPLICATE_SCHEDULE_ID 			= 0x05;
const int ApplicationException::APPLICATION_EXITVALUE_NOT_AVAILABLE		 	= 0x06;
const int ApplicationException::APPLICATION_INVALID_STARTUP_ARGUMENT 		= 0x07;
											 
osgi::svc::ApplicationException::ApplicationException(int errorCode)
  : Exception("")
  , errorCode(errorCode)
{
}

osgi::svc::ApplicationException::ApplicationException(int errorCode, const ctkException& cause)
  : Exception("", cause)
  , errorCode(errorCode)
{
}

osgi::svc::ApplicationException::ApplicationException(int errorCode, const QString& message)
  : Exception(message)
  , errorCode(errorCode)
{
}

osgi::svc::ApplicationException::ApplicationException(int errorCode, const QString& message, const ctkException& cause)
  : Exception(message, cause)
  , errorCode(errorCode)
{
}

osgi::svc::ApplicationException::~ApplicationException() throw()
{
}

const char* osgi::svc::ApplicationException::name() const throw()
{
	return "Application Exception";
}

osgi::svc::ApplicationException* osgi::svc::kApplicationException::clone() const
{
	return new ApplicationException(*this);
}

void osgi::svc::ApplicationException::rethrow() const
{
	throw *this;
}

int osgi::svc::ApplicationException::GetErrorCode() const
{
	return errorCode;
}
