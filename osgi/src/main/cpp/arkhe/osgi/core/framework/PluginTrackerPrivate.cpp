#include <arkhe/osgi/core/framework/PluginTrackerPrivate.hpp>

template<class T>
osgi::core::PluginTrackerPrivate<T>::PluginTrackerPrivate()
{
}

template<class T>
osgi::core::PluginTrackerPrivate<T>::PluginTrackerPrivate(PluginTracker<T>* pt, PluginContext* context,
    Plugin::States stateMask, PluginTrackerCustomizer<T>* customizer)
  : context(context)
  , customizer(customizer)
  , mask(stateMask)
  , q_ptr(pt)
{
  this->customizer = customizer ? customizer : q_func();
}


template<class T>
osgi::core::PluginTrackerPrivate<T>::~PluginTrackerPrivate()
{
	  if (customizer != q_func())
  {
    delete customizer;
  }
}

template<class T>
QSharedPointer<osgi::core::TrackedPlugin<T> > osgi::core::PluginTrackerPrivate<T>::tracked() const
{
  return trackedPlugin;
}
