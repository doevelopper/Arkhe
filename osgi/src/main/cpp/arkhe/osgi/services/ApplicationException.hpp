#ifndef ARKHE_OSGI_SERVICES_APPLICATIONEXCEPTION_HPP
#define ARKHE_OSGI_SERVICES_APPLICATIONEXCEPTION_HPP

#include <arkhe/osgi/core/Exception.hpp>

/*!
 * @brief 
 * 	
 */
namespace osgi
{
	namespace svc
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT ApplicationException
		{

		public:
			ApplicationException();
			virtual ~ApplicationException() throw();
			ApplicationException(int errorCode);
			ApplicationException(int errorCode, const Exception& cause);
			ApplicationException(int errorCode, const QString& message);
			ApplicationException(int errorCode, const QString& message, const Exception& cause);

			const char* name() const throw();
			ApplicationException* clone() const;
			void rethrow() const;
			int GetErrorCode() const;

			static const int APPLICATION_LOCKED; 					// = 0x01;	
			static const int APPLICATION_NOT_LAUNCHABLE; 			// = 0x02;
			static const int APPLICATION_INTERNAL_ERROR; 			// = 0x03;
			static const int APPLICATION_SCHEDULING_FAILED; 		// = 0x04;
			static const int APPLICATION_DUPLICATE_SCHEDULE_ID; 	// = 0x05;
			static const int APPLICATION_EXITVALUE_NOT_AVAILABLE; 	// = 0x06;
			static const int APPLICATION_INVALID_STARTUP_ARGUMENT; 	// = 0x07;
		protected:

		private:

			int errorCode;
		};		
	}
}

#endif
