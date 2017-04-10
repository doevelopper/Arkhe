#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEVENT_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEVENT_HPP

#include <QSharedDataPointer>
#include <QDebug>
#include <QMetaType>

#include <arkhe/osgi/core/framework/ServiceReference.hpp>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */

namespace osgi
{
	namespace core
	{
		class ServiceEventData;
		
		class ARKHE_CORE_PLUGIN_FW_EXPORT ServiceEvent
		{

		public:
			enum Type 
			{
				REGISTERED = 0x00000001,
				MODIFIED = 0x00000002,
				UNREGISTERING = 0x00000004,
				MODIFIED_ENDMATCH = 0x00000008

			};

			ServiceEvent();
			ServiceEvent(const ServiceEvent& other);
			ServiceEvent(Type type, const ServiceReference& reference);
			ServiceEvent& operator=(const ServiceEvent& other);
			ServiceReference getServiceReference() const;
			virtual ~ServiceEvent();

			bool isNull() const;
			Type getType() const;
		protected:

		private:

			QSharedDataPointer<ServiceEventData> d;
		};

		Q_DECLARE_METATYPE(osgi::core::ServiceEvent)		
	}
}

ARKHE_CORE_PLUGIN_FW_EXPORT QDebug operator<<(QDebug dbg, osgi::core::ServiceEvent::Type type);
ARKHE_CORE_PLUGIN_FW_EXPORT QDebug operator<<(QDebug dbg, const osgi::core::ServiceEvent& event);

#endif
