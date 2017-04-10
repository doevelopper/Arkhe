#ifndef ARKHE_OSGI_CORE_FRAMEWORK_PLUGINTRACKERPRIVATE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_PLUGINTRACKERPRIVATE_HPP

#include <QString>
#include <QRegExp>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		template<class T>
		class PluginTrackerPrivate
		{

		public:

			PluginTrackerPrivate();
			PluginTrackerPrivate(PluginTracker<T>* pt, PluginContext* context, Plugin::States stateMask, PluginTrackerCustomizer<T>* customizer);
			QSharedPointer<TrackedPlugin<T> > tracked() const;
			virtual ~PluginTrackerPrivate();
			
			PluginContext* const context;
			PluginTrackerCustomizer<T>* customizer;
			QSharedPointer<TrackedPlugin<T> > trackedPlugin;
			
			Plugin::States mask;
			mutable QMutex mutex;

		protected:

		private:
			inline PluginTracker<T>* q_func()
			{
				return static_cast<PluginTracker<T> *>(q_ptr);
			}

			inline const PluginTracker<T>* q_func() const
			{
				return static_cast<const PluginTracker<T> *>(q_ptr);
			}

			friend class PluginTracker<T>;
			PluginTracker<T> * const q_ptr;

		};		
	}
}
#endif
