#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKERPRIVATE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKERPRIVATE_HPP

#include <QMutex>
#include <QSharedPointer>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceReference.hpp>
// #include <arkhe/osgi/core/framework/LDAPSearchFilter.hpp>
class QVariant;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		template<class S, class T>
		class ServiceTrackerPrivate
		{

		public:
			ServiceTrackerPrivate();
			ServiceTrackerPrivate(ServiceTracker<S,T>* st, PluginContext* context, const ServiceReference& reference, ServiceTrackerCustomizer<T>* customizer);
			ServiceTrackerPrivate(ServiceTracker<S,T>* st, PluginContext* context, const QString& clazz, ServiceTrackerCustomizer<T>* customizer);
			ServiceTrackerPrivate(ServiceTracker<S,T>* st, PluginContext* context, const LDAPSearchFilter& filter,ServiceTrackerCustomizer<T>* customizer);
			virtual ~ServiceTrackerPrivate();
			
			QList<ServiceReference> getInitialReferences(const QString& className, const QString& filterString);
			QList<ServiceReference> getServiceReferences_unlocked(TrackedService<S,T>* t) const;

			/* set this to true to compile in debug messages */
			static const bool	DEBUG_FLAG; //	= false;
			PluginContext* const	context;
			LDAPSearchFilter	filter;
			ServiceTrackerCustomizer<T>* customizer;
			QString listenerFilter;
			QString trackClass;
			ServiceReference	trackReference;
			QSharedPointer<TrackedService<S,T> > trackedService;
			QSharedPointer<TrackedService<S,T> > tracked() const;
			void modified();

			mutable ServiceReference cachedReference;
			mutable T volatile cachedService;
			mutable QMutex mutex;
			
		protected:

		private:
			inline ServiceTracker<S,T>* q_func()
			{
				return static_cast<ServiceTracker<S,T> *>(q_ptr);
			}

			inline const ServiceTracker<S,T>* q_func() const
			{
				return static_cast<const ServiceTracker<S,T> *>(q_ptr);
			}
			
			friend class ServiceTracker<S,T>;
			ServiceTracker<S,T> * const q_ptr;
		};		
	}
}
#endif
