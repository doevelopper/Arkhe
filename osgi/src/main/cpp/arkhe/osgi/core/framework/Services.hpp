#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICES_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICES_HPP

#include <QHash>
#include <QObject>
#include <QMutex>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceRegistration.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class  Services
		{
		
		public:
			Services();
			Services(PluginFrameworkContext* fwCtx);
			virtual ~Services();
			
			mutable QMutex mutex;
			static osgi::Dictionary createServiceProperties(const osgi::Dictionary& in, const QStringList& classes = QStringList(), long sid = -1);
			void updateServiceRegistrationOrder(const ServiceRegistration& sr, const QStringList& classes);
			bool checkServiceClass(QObject* service, const QString& cls) const;
			QList<ServiceRegistration> get(const QString& clazz) const;
			void removeServiceRegistration(const ServiceRegistration& sr) ;
			QList<ServiceRegistration> getRegisteredByPlugin(PluginPrivate* p) const;
			QList<ServiceRegistration> getUsedByPlugin(QSharedPointer<Plugin> p) const;
			QList<ServiceReference> get(const QString& clazz, const QString& filter, PluginPrivate* plugin) const;
			ServiceRegistration registerService(PluginPrivate* plugin, const QStringList& classes, QObject* service, const osgi::Dictionary& properties);
			ServiceReference get(PluginPrivate* plugin, const QString& clazz) const;
			QHash<ServiceRegistration, QStringList> services;
			QHash<QString, QList<ServiceRegistration> > classServices;
			PluginFrameworkContext* framework;
			void clear();
		protected:

		private:
	
			QList<ServiceReference> get_unlocked(const QString& clazz, const QString& filter, PluginPrivate* plugin) const;
		};		
	}
}
#endif
