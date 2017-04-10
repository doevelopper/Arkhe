#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREFERENCEPRIVATE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREFERENCEPRIVATE_HPP

#include <QAtomicInt>
#include <QSharedPointer>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceProperties.hpp>

class QObject;


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ServiceRegistrationPrivate;
		class Plugin;

		class ServiceReferencePrivate
		{

		public:
			ServiceReferencePrivate();
			ServiceReferencePrivate(ServiceRegistrationPrivate* reg);
			virtual ~ServiceReferencePrivate();

			const ServiceProperties& getProperties() const;
			QObject* getService(QSharedPointer<Plugin> plugin);
			bool ungetService(QSharedPointer<Plugin> plugin, bool checkRefCounter);
			QVariant getProperty(const QString& key, bool lock) const;

			QAtomicInt ref;
			ServiceRegistrationPrivate* const registration;
		protected:

		private:
			Q_DISABLE_COPY(ServiceReferencePrivate)
		};		
	}
}
#endif
