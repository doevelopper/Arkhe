#ifndef ARKHE_OSGI_CORE_FRAMEWORK_PLUGINTRACKERCUSTOMIZER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_PLUGINTRACKERCUSTOMIZER_HPP

#include <QVariant>
#include <arkhe/osgi/core/framework/PluginEvent.hpp>
#include <arkhe/osgi/osgi.hpp>

class QObject;

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class Plugin;

		template<class T>
		class PluginTrackerCustomizer
		{

		public:
			PluginTrackerCustomizer();
			virtual ~PluginTrackerCustomizer();
			virtual T addingPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event) = 0;
			virtual void modifiedPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event, T object) = 0;
			virtual void removedPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event, T object) = 0;
		protected:

		private:

		};		
	}
}
#endif
