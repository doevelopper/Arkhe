#ifndef ARKHE_OSGI_SERVICES_APPLICATIONHANDLE_HPP
#define ARKHE_OSGI_SERVICES_APPLICATIONHANDLE_HPP

#include <arkhe/osgi/osgi.hpp>

#include <QObject>
#include <QString>

class QVariant;
class ApplicationDescriptor;

/*!
 * @brief 
 * 
 */
namespace osgi
{
	namespace svc
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT ApplicationHandle
		{

		public:
			ApplicationHandle();
			virtual ~ApplicationHandle();
			virtual ApplicationDescriptor* getApplicationDescriptor() const = 0;
			virtual QString getState() const = 0;
			virtual QVariant getExitValue(long timeout) const = 0;
			virtual QString getInstanceId() const = 0;
			virtual void destroy() = 0;
		protected:

		private:
			static const QString APPLICATION_PID; 				// = ctkPluginConstants::SERVICE_PID;
			static const QString APPLICATION_DESCRIPTOR; 		// = "application.descriptor";
			static const QString APPLICATION_STATE; 			// = "application.state";
			static const QString APPLICATION_SUPPORTS_EXITVALUE; // = "application.supports.exitvalue";
			static const QString RUNNING; 
			static const QString STOPPING;
		};		
	}
}
Q_DECLARE_INTERFACE(osgi::svc::ApplicationHandle, "000.levitics.arkhe.service.application.ApplicationHandle")
#endif
