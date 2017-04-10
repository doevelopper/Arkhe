#include <arkhe/osgi/core/framework/ServiceException.hpp>

osgi::core::ServiceException::ServiceException()
{
}

osgi::core::ServiceException::ServiceException(const QString& msg, const Type& type)
  : RuntimeException(msg),
    type(type)
{

}

osgi::core::ServiceException::~ServiceException() throw()
{
}

osgi::core::ServiceException::ServiceException(const QString& msg, const Type& type,
                                         const Exception& cause)
  : RuntimeException(msg, cause),
    type(type)
{

}

osgi::core::ServiceException::ServiceException(const QString& msg, const Exception& cause)
  : RuntimeException(msg, cause),
    type(UNSPECIFIED)
{

}

osgi::core::ServiceException::ServiceException(const ServiceException& o)
  : RuntimeException(o), type(o.type)
{

}

osgi::core::ServiceException& osgi::core::ServiceException::operator=(const ServiceException& o)
{
  RuntimeException::operator=(o);
  type = o.type;
  return *this;
}


const char* osgi::core::ServiceException::name() const throw()
{
  return "ServiceException";
}

osgi::core::ServiceException* osgi::core::ServiceException::clone() const
{
	return new ServiceException(*this);
}

void osgi::core::ServiceException::rethrow() const
{
  throw *this;
}

osgi::core::ServiceException::Type ctkServiceException::getType() const
{
  return type;
}
