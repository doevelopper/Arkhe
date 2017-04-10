#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREGISTRATION_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEREGISTRATION_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceReference.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ServiceRegistrationPrivate;

		class ARKHE_CORE_PLUGIN_FW_EXPORT ServiceRegistration
		{

		public:
			ServiceRegistration();
			ServiceRegistration(const ServiceRegistration& reg);
			virtual ~ServiceRegistration();
			operator bool() const;
			ServiceRegistration& operator=(int null);
			ServiceReference getReference() const;
			void setProperties(const osgi::Dictionary& properties);
			void unregister();

			bool operator<(const ServiceRegistration& o) const;
			bool operator==(const ServiceRegistration& registration) const;
			ServiceRegistration& operator=(const ServiceRegistration& registration);

		protected:

			friend class Services;
			friend class ServiceReferencePrivate;

			friend uint ARKHE_CORE_PLUGIN_FW_EXPORT qHash(const ServiceRegistration&);

			ServiceRegistration(ServiceRegistrationPrivate* registrationPrivate);
			ServiceRegistration(PluginPrivate* plugin, QObject* service, const ctkDictionary& props);

			ServiceRegistrationPrivate* d_ptr;

		private:

			Q_DECLARE_PRIVATE(osgi::core::ServiceRegistration)
		};		
	}
}
uint ARKHE_CORE_PLUGIN_FW_EXPORT qHash(const osgi::core::ServiceRegistration& serviceRef);
#endif
