#include <arkhe/osgi/core/framework/PluginTracker.hpp>

template<class T>
osgi::core::PluginTracker<T>::PluginTracker()
{
}

template<class T>
osgi::core::PluginTracker<T>::PluginTracker(PluginContext* context, Plugin::States stateMask,
                                      PluginTrackerCustomizer<T>* customizer)
  : d_ptr(new PluginTrackerPrivate<T>(this, context, stateMask, customizer))
{

}

osgi::core::PluginTracker<T>::~PluginTracker()
{
}

template<class T>
void osgi::core::PluginTracker<T>::open()
{
  Q_D(PluginTracker<T>);
  QSharedPointer<TrackedPlugin<T>> t;
  {
    QMutexLocker lock(&d->mutex);
    if (d->trackedPlugin)
    {
      return;
    }


    t = QSharedPointer<TrackedPlugin<T>>(new TrackedPlugin<T>(this, d->customizer));
    {
      QMutexLocker lockT(t.data());
      d->context->connectPluginListener(t.data(), SLOT(pluginChanged(PluginEvent)), Qt::DirectConnection);
      QList<QSharedPointer<Plugin> > plugins = d->context->getPlugins();
      int length = plugins.size();
      for (int i = 0; i < length; i++)
      {
        Plugin::State state = plugins[i]->getState();
        if ((d->mask & state) == 0)
        {
          /* null out plugins whose states are not interesting */
          plugins[i].clear();
        }
      }
      plugins.removeAll(QSharedPointer<Plugin>());
      /* set tracked with the initial bundles */
      t->setInitial(plugins);
    }
    d->trackedPlugin = t;
  }
  /* Call tracked outside of synchronized region */
  t->trackInitial(); /* process the initial references */
}

template<class T>
void osgi::core::PluginTracker<T>::close()
{
  Q_D(PluginTracker<T>);
  QList<QSharedPointer<Plugin> > plugins;
  QSharedPointer<TrackedPlugin<T>> outgoing;
  {
    QMutexLocker lock(&d->mutex);
    outgoing = d->trackedPlugin;
    if (outgoing.isNull())
    {
      return;
    }


    outgoing->close();
    plugins = getPlugins();
    d->trackedPlugin.clear();;

    outgoing->disconnect(SLOT(pluginChanged(PluginEvent)));
  }

  foreach (QSharedPointer<Plugin> plugin, plugins)
  {
    outgoing->untrack(plugin, PluginEvent());
  }
}

template<class T>
QList<QSharedPointer<osgi::core::Plugin> > osgi::core::PluginTracker<T>::getPlugins() const
{
  Q_D(const PluginTracker<T>);
  QSharedPointer<TrackedPlugin<T>> t = d->tracked();
  if (t.isNull())
  { /* if ctkPluginTracker is not open */
    return QList<QSharedPointer<Plugin> >();
  }

  {
    QMutexLocker lock(t.data());
    return t->getTracked();
  }
}

template<class T>
T osgi::core::PluginTracker<T>::getObject(QSharedPointer<Plugin> plugin) const
{
  Q_D(const PluginTracker<T>);
  QSharedPointer<TrackedPlugin<T>> t = d->tracked();
  if (t.isNull())
  {
    return T();
  }

  {
    QMutexLocker lock(t.data());
    return t->getCustomizedObject(plugin);
  }
}

template<class T>
void osgi::core::PluginTracker<T>::remove(QSharedPointer<Plugin> plugin)
{
  Q_D(PluginTracker<T>);
  QSharedPointer<TrackedPlugin<T>> t = d->tracked();
  if (t.isNull())
  {
    return;
  }
  t->untrack(plugin, PluginEvent());
}

//----------------------------------------------------------------------------
template<class T>
int osgi::core::PluginTracker<T>::size() const
{
  Q_D(const PluginTracker<T>);
  QSharedPointer<TrackedPlugin>T>> t = d->tracked();
  if (t.isNull())
  {
    return 0;
  }

  {
    QMutexLocker lock(t.data());
    return t->size();
  }
}

template<class T>
int osgi::core::PluginTracker<T>::getTrackingCount() const
{
  Q_D(const PluginTracker<T>);
  QSharedPointer<TrackedPlugin<T>> t = d->tracked();
  if (t.isNull())
  {
    return -1;
  }

  {
    QMutexLocker lock(t.data());
    return t->getTrackingCount();
  }
}

template<class T>
QMap<QSharedPointer<osgi::core::Plugin>, T> osgi::core::PluginTracker<T>::getTracked() const
{
  QMap<QSharedPointer<Plugin>, T> map;
  Q_D(const PluginTracker<T>);
  QSharedPointer<TrackedPlugin<T>> t = d->tracked();
  if (t.isNull())
  { /* if PluginTracker is not open */
    return map;
  }
  {
    QMutexLocker lock(t.data());
    return t->copyEntries(map);
  }
}

template<class T>
bool osgi::core::PluginTracker<T>::isEmpty() const
{
  Q_D(const PluginTracker<T>);
  QSharedPointer<TrackedPlugin<T> > t = d->tracked();
  if (t.isNull())
  { /* if PluginTracker is not open */
    return true;
  }
  {
    QMutexLocker lock(t.data());
    return t->isEmpty();
  }
}

template<>
inline QSharedPointer<osgi::core::Plugin> osgi::core::PluginTracker<QSharedPointer<Plugin> >::addingPlugin(QSharedPointer<Plugin> plugin
, const PluginEvent& event)
{
  Q_UNUSED(event)
  return plugin;
}

template<class T>
T osgi::core::PluginTracker<T>::addingPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event)
{
  Q_UNUSED(plugin)
  Q_UNUSED(event)

  return 0;
}

template<class T>
void osgi::core::PluginTracker<T>::modifiedPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event, T object)
{
  Q_UNUSED(plugin)
  Q_UNUSED(event)
  Q_UNUSED(object)
  /* do nothing */
}

//----------------------------------------------------------------------------
template<class T>
void osgi::core::PluginTracker<T>::removedPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event, T object)
{
  Q_UNUSED(plugin)
  Q_UNUSED(event)
  Q_UNUSED(object)
  /* do nothing */
}

