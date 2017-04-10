#ifndef ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDPLUGIN_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDPLUGIN_HPP

#include <QSharedPointer>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/TrackedPluginListener.hpp>
#include <arkhe/osgi/core/framework/PluginAbstractTracked.hpp>
#include <arkhe/osgi/core/framework/Plugin.hpp>
#include <arkhe/osgi/core/framework/PluginEvent.hpp>

class QVariant;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		template<class T>
		class  TrackedPlugin : public TrackedPluginListener, public PluginAbstractTracked<QSharedPointer<Plugin>, T, PluginEvent>
		{

		public:
			TrackedPlugin();
			TrackedPlugin(PluginTracker<T>* pluginTracker,PluginTrackerCustomizer<T>* customizer);
			virtual ~TrackedPlugin();
			
			void pluginChanged(const PluginEvent& event);
			
		protected:

		private:

			T customizerAdding(QSharedPointer<Plugin> item, const PluginEvent& related);
			void customizerModified(QSharedPointer<Plugin> item, const PluginEvent& related, T object);
			void customizerRemoved(QSharedPointer<Plugin> item, const PluginEvent& related, T object);
			using Superclass = PluginAbstractTracked<QSharedPointer<Plugin>, T, PluginEvent> Superclass;
			PluginTracker<T>* pluginTracker;
			PluginTrackerCustomizer<T>* customizer;
		};		
	}
}
#endif
