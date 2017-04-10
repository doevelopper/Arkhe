#ifndef ARKHE_OSGI_CORE_FRAMEWORK_PLUGINTRACKER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_PLUGINTRACKER_HPP

#include <QScopedPointer>

#include <arkhe/osgi/core/framework/Plugin.hpp>
#include <arkhe/osgi/core/framework/PluginTrackerCustomize.hpp>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		template<class T> class TrackedPlugin;
		template<class T> class PluginTrackerPrivate;

		template<class T = QSharedPointer<Plugin> >
		class PluginTracker : protected PluginTrackerCustomizer<T>
		{

		public:
			PluginTracker();
			PluginTracker(PluginContext* context, Plugin::States stateMask, PluginTrackerCustomizer<T>* customizer = 0);
			virtual ~PluginTracker();

			virtual void open();
			virtual void close();
			virtual QList<QSharedPointer<Plugin> > getPlugins() const;
			virtual T getObject(QSharedPointer<Plugin> plugin) const;
			virtual void remove(QSharedPointer<Plugin> plugin);
			virtual int size() const;
			virtual int getTrackingCount() const;
			virtual QMap<QSharedPointer<Plugin>, T> getTracked() const;
			virtual bool isEmpty() const;

		protected:
			
			T addingPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event);
			void modifiedPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event, T object);
			void removedPlugin(QSharedPointer<Plugin> plugin, const PluginEvent& event, T object);

			friend class TrackedPlugin<T>;
			friend class PluginTrackerPrivate<T>;
  
		private:

			// using PluginTracker = PluginTracker<T>;
			// using TrackedPlugin = TrackedPlugin<T>;
			// using PluginTrackerPrivate = PluginTrackerPrivate<T>;
			// using PluginTrackerCustomizer = PluginTrackerCustomizer<T>;
			
			inline PluginTrackerPrivate<T> * d_func()
			{
				return reinterpret_cast< PluginTrackerPrivate<T> *>(qGetPtrHelper(d_ptr));
			}

			inline const PluginTrackerPrivate<T> * d_func() const
			{
				return reinterpret_cast<const PluginTrackerPrivate<T> *>(qGetPtrHelper(d_ptr));
			}

			const QScopedPointer<PluginTrackerPrivate<T> > d_ptr;
			
		};		
	}
}
#endif
