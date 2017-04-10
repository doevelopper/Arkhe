#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKERCUSTOMIZER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKERCUSTOMIZER_HPP


#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		template<class T = QObject*>
		class ServiceTrackerCustomizer
		{

		public:
			ServiceTrackerCustomizer();
			virtual ~ServiceTrackerCustomizer();
			
			virtual T addingService(const ServiceReference& reference) = 0;
			virtual void modifiedService(const ServiceReference& reference, T service) = 0;
			virtual void removedService(const ServiceReference& reference, T service) = 0;
			
		protected:

		private:

		};		
	}
}
#endif
