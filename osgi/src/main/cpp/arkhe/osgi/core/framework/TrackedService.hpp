#ifndef ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDSERVICE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDSERVICE_HPP


#include <arkhe/osgi/osgi.hpp>

class QVariant;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		template<class S, class T>
		class TrackedService : public TrackedServiceListener, public PluginAbstractTracked<ServiceReference, T, ServiceEvent>
		{

		public:
			TrackedService();
			TrackedService(ServiceTracker<S,T>* serviceTracker,ServiceTrackerCustomizer<T>* customizer);
			void serviceChanged(const ServiceEvent& event);
			virtual ~TrackedService();
		protected:

		private:
			void modified();
			T customizerAdding(ServiceReference item, const ServiceEvent& related);
			void customizerModified(ServiceReference item, const ServiceEvent& related, T object) ;
			void customizerRemoved(ServiceReference item, const ServiceEvent& related, T object) ;
			
			using Superclass = PluginAbstractTracked<ServiceReference, T, ServiceEvent>;
			
			ServiceTracker<S,T>* serviceTracker;
			ServiceTrackerCustomizer<T>* customizer;
		};		
	}
}
#endif
