#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEVENTDATA_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEVENTDATA_HPP

#include <arkhe/osgi/core/framework/ServiceReference.hpp>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */

namespace osgi
{
	namespace core
	{
		
		class ARKHE_CORE_PLUGIN_FW_EXPORT ServiceEventData : public QSharedData
		{

		public:

			ServiceEventData();
			ServiceEventData(ServiceEvent::Type type, const ServiceReference& reference);
			ServiceEventData(const ServiceEventData& other);
			virtual ~ServiceEventData();

			const ServiceEvent::Type type;
			const ServiceReference reference;
  
		protected:

		private:

		};		
	}
}
#endif
