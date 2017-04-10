#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREFERENCE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREFERENCE_HPP

#include <QVariant>
#include <QMetaType>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/Plugin.hpp>
class QVariant;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		
		class ServiceRegistrationPrivate;
		class ServiceReferencePrivate;
		class ServiceEvent;

		class ARKHE_CORE_PLUGIN_FW_EXPORT ServiceReference
		{

		public:

			ServiceReference();
			ServiceReference(const ServiceReference& ref);
			virtual ~ServiceReference();

			operator bool() const;
			ServiceReference& operator=(int null);
			QVariant getProperty(const QString& key) const;
			QStringList getPropertyKeys() const;
			QSharedPointer<Plugin> getPlugin() const;
			QList<QSharedPointer<Plugin> > getUsingPlugins() const;
			
			bool operator<(const ServiceReference& reference) const;
			bool operator==(const ServiceReference& reference) const;
			ServiceReference& operator=(const ServiceReference& reference);

			
  
		protected:

			// friend class LDAPSearchFilter;
			friend class ServiceRegistrationPrivate;
			friend class PluginContext;
			friend class PluginPrivate;
			friend class PluginFrameworkListeners;
			template<class S, class T> 
			friend class ServiceTracker;
			template<class S, class T> 
			friend class ServiceTrackerPrivate;
			template<class S, class R, class T> 
			friend class PluginAbstractTracked;

			friend uint ARKHE_CORE_PLUGIN_FW_EXPORT qHash(const ServiceReference&);
			ServiceReference(ServiceRegistrationPrivate* reg);
			ServiceReferencePrivate * d_ptr;
			

		private:
			Q_DECLARE_PRIVATE(ServiceReference)
		};
		uint ARKHE_CORE_PLUGIN_FW_EXPORT qHash(const osgi::core::ServiceReference& serviceRef);
		QDebug ARKHE_CORE_PLUGIN_FW_EXPORT operator<<(QDebug dbg, const osgi::core::ServiceReference& serviceRef);
		Q_DECLARE_METATYPE(ServiceReference)		
	}
}
#endif
