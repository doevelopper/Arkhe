#ifndef ARKHE_OSGI_SERVICES_APPLICATIONDESCRIPTOR_HPP
#define ARKHE_OSGI_SERVICES_APPLICATIONDESCRIPTOR_HPP

#include <arkhe/osgi/osgi.hpp>

#include <QHash>
#include <QVariant>
#include <QString>
#include <QLocale>

class ApplicationHandle;

/*!
 * @brief 
 * 
 */
namespace osgi
{
	namespace svc
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT ApplicationDescriptor
		{

		public:
			ApplicationDescriptor();
			virtual ~ApplicationDescriptor();
			virtual QString getApplicationId() const = 0;
			// virtual ctkProperties getProperties(const QLocale& locale) const = 0;
			// virtual ctkProperties getProperties() const = 0;
			virtual ApplicationHandle* launch(const QHash<QString, QVariant>& arguments) = 0;

		protected:

		private:
			static const QString APPLICATION_NAME;
			static const QString APPLICATION_ICON;
			static const QString APPLICATION_PID;
			static const QString APPLICATION_VERSION;
			static const QString APPLICATION_VENDOR;
			static const QString APPLICATION_VISIBLE;
			static const QString APPLICATION_LAUNCHABLE;
			static const QString APPLICATION_LOCKED;
			static const QString APPLICATION_DESCRIPTION;
			static const QString APPLICATION_DOCUMENTATION;
			static const QString APPLICATION_COPYRIGHT;
			static const QString APPLICATION_LICENSE;
			static const QString APPLICATION_CONTAINER;
			static const QString APPLICATION_LOCATION;
		};		
	}
}
Q_DECLARE_INTERFACE(ApplicationDescriptor, "000.levitics.arkhe.service.application.ApplicationDescriptor")
#endif
