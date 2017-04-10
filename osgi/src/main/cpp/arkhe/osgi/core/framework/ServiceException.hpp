#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEXCEPTION_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEXCEPTION_HPP

#include <arkhe/osgi/core/framework/ServiceException.hpp>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT ServiceException //: public RuntimeException
		{

		public:
		  enum Type 
		  {
			UNSPECIFIED = 0,
			UNREGISTERED = 1,
			FACTORY_ERROR = 2,
			FACTORY_EXCEPTION = 3,
			REMOTE = 5,
			FACTORY_RECURSION = 6
		  };

			ServiceException();
			virtual ~ServiceException() throw();

			ServiceException(const QString& msg, const Type& type = UNSPECIFIED);
			ServiceException(const QString& msg, const Type& type, const Exception& cause);
			ServiceException(const QString& msg, const Exception& cause);

			ServiceException(const ServiceException& o);
			ServiceException& operator=(const ServiceException& o);

			const char* name() const throw();
			ServiceException* clone() const;
			void rethrow() const;
			Type getType() const;
		protected:

		private:
			Type type;
		};		
	}
}
#endif
