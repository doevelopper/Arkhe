#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEFACTORY_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEFACTORY_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceRegistration.hpp>
#include <arkhe/osgi/core/framework/Plugin.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ServiceFactory
		{

		public:

			ServiceFactory();
			virtual ~ServiceFactory();
			virtual QObject* getService(QSharedPointer<Plugin> plugin, ServiceRegistration registration) = 0;
			virtual void ungetService(QSharedPointer<Plugin> plugin, ServiceRegistration registration, QObject* service) = 0;

		protected:

		private:

		};
		Q_DECLARE_INTERFACE(osgi::core::ServiceFactory, "org.commontk.services.ServiceFactory")		
	}
}
#endif
