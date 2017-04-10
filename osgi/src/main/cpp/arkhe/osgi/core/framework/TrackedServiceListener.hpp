#ifndef ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDSERVICELISTENER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDSERVICELISTENER_HPP

#include <QObject>
#include <arkhe/osgi/core/framework/ServiceEvent.hpp>
#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT TrackedServiceListener : public QObject
		{
			Q_OBJECT

		public:

			TrackedServiceListener(QObject *parent = 0);
			virtual ~TrackedServiceListener();

		public Q_SLOTS:

			virtual void serviceChanged(const ServiceEvent& event) = 0;

		protected:

		private:

		};		
	}
}
#endif
