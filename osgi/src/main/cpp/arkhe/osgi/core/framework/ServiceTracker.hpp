#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKER_HPP


#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/ServiceReference.hpp>
#include <arkhe/osgi/core/framework/ServiceTrackerCustomizer.hpp>
#include <arkhe/osgi/core/framework/LDAPSearchFilter.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		template<class S, class T> 
			class TrackedService;
		template<class S, class T> 
			class ServiceTrackerPrivate;
		class PluginContext;
		
		template<class S = QObject*, class T = S>
		class ServiceTrackerr : protected ServiceTrackerCustomizer<T>
		{

		public:
			ServiceTracker();
			ServiceTracker(PluginContext* context, const QString& clazz, ServiceTrackerCustomizer<T>* customizer = 0);
			ServiceTracker(PluginContext* context, const LDAPSearchFilter& filter, ServiceTrackerCustomizer<T>* customizer = 0);
			ServiceTracker(PluginContext* context, ServiceTrackerCustomizer<T>* customizer = 0);
			virtual ~ServiceTracker();
			
			virtual void open();
			virtual void close();
			virtual T waitForService(unsigned long timeout);
			virtual QList<ServiceReference> getServiceReferences() const;
			virtual ServiceReference getServiceReference() const;
			virtual T getService(const ServiceReference& reference) const;
			virtual QList<T> getServices() const;
			virtual T getService() const;
			virtual void remove(const ctkServiceReference& reference);
			virtual int size() const;
			virtual int getTrackingCount() const;
			virtual QMap<ServiceReference, T> getTracked() const;
			virtual bool isEmpty() const;

		protected:

			T addingService(const ServiceReference& reference);
			void modifiedService(const ServiceReference& reference, T service);
			void removedService(const ServiceReference& reference, T service);
			
		private:

			using _ServiceTracker = ServiceTracker<S,T>;
			using _TrackedService = TrackedService<S,T>;
			using _ServiceTrackerPrivate =  ServiceTrackerPrivate<S,T> ;
			using _ServiceTrackerCustomizer = ServiceTrackerCustomizer<T>;
			
			friend class TrackedService<S,T>;
			friend class ServiceTrackerPrivate<S,T>;
  
			inline kServiceTrackerPrivate<S,T>* d_func()
			{
				return reinterpret_cast<kServiceTrackerPrivate<S,T>*>(qGetPtrHelper(d_ptr));
			}

			inline const kServiceTrackerPrivate<S,T>* d_func() const
			{
				return reinterpret_cast<const kServiceTrackerPrivate<S,T>*>(qGetPtrHelper(d_ptr));
			}
			
			const QScopedPointer<kServiceTrackerPrivate<S,T>> d_ptr;
		};		
	}
}
#endif
