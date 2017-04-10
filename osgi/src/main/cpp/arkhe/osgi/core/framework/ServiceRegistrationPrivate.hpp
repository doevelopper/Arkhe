#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREGISTRATIONPRIVATE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREGISTRATIONPRIVATE_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceReference.hpp>
#include <arkhe/osgi/core/framework/ServiceProperties.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class PluginPrivate;
		class ServiceRegistration;

		class ServiceRegistrationPrivate
		{

		public:
			ServiceRegistrationPrivate();
			ServiceRegistrationPrivate(PluginPrivate* plugin, QObject* service, const osgi::Dictionary& props);
			virtual ~ServiceRegistrationPrivate();

			bool isUsedByPlugin(QSharedPointer<Plugin> p);
			virtual QObject* getService();

			PluginPrivate* plugin;
			ServiceReference reference;
			ServiceProperties properties;
			QHash<QSharedPointer<Plugin>,int> dependents;
			QHash<QSharedPointer<Plugin>, QObject*> serviceInstances;
			volatile bool available;
			volatile bool unregistering;
			QMutex eventLock;
			QMutex propsLock;

		protected:
			friend class ServiceRegistration;
			friend class ServiceReferencePrivate;
			QAtomicInt ref;
			QObject* service;
		private:
			Q_DISABLE_COPY(ServiceRegistrationPrivate)
		};		
	}
}
#endif
