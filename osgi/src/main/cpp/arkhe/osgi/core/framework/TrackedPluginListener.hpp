#ifndef ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDPLUGINLISTENER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDPLUGINLISTENER_HPP

#include <QObject>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/PluginEvent.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT TrackedPluginListener : public QObject
		{

		public:

			TrackedPluginListener(QObject *parent = 0);
			virtual ~TrackedPluginListener();

		public Q_SLOTS:

			virtual void pluginChanged(const PluginEvent& event) = 0;

		protected:

		private:

		};		
	}
}
#endif
