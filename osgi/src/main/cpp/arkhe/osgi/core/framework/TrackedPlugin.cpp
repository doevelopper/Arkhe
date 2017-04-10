#include <arkhe/osgi/core/framework/TrackedPlugin.hpp>

template<class T>
osgi::core::TrackedPlugin<T>::TrackedPlugin()
{
}

template<class T>
osgi::core::TrackedPlugin<T>::TrackedPlugin(PluginTracker<T>* pluginTracker, PluginTrackerCustomizer<T>* customizer)
  : pluginTracker(pluginTracker)
  , customizer(customizer)
{

}

template<class T>
osgi::core::TrackedPlugin<T>::~TrackedPlugin()
{
}

template<class T>
void osgi::core::TrackedPlugin<T>::pluginChanged(const PluginEvent& event)
{

	if (this->closed)
	{
		return;
	}

	QSharedPointer<Plugin> plugin = event.getPlugin();
	Plugin::State state = plugin->getState();

	if (pluginTracker->d_func()->DEBUG_FLAG)
	{
		qDebug() << "TrackedPlugin<T>::pluginChanged[" << state << "]: " << *plugin;
	}

	if (pluginTracker->d_func()->mask & state)
	{
		this->track(plugin, event);
	}
	else
	{
		this->untrack(plugin, event);
	}
}

//----------------------------------------------------------------------------
template<class T>
T osgi::core::TrackedPlugin<T>::customizerAdding(QSharedPointer<Plugin> item, const PluginEvent& related)
{
	return customizer->addingPlugin(item, related);
}

template<class T>
void osgi::core::TrackedPlugin<T>::customizerModified(QSharedPointer<Plugin> item, const PluginEvent& related, T object)
{
	customizer->modifiedPlugin(item, related, object);
}

template<class T>
void osgi::core::TrackedPlugin<T>::customizerRemoved(QSharedPointer<Plugin> item, const PluginEvent& related,  T object)
{
	customizer->removedPlugin(item, related, object);
}


