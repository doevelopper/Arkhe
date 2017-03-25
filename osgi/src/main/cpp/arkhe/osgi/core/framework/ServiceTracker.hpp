#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICETRACKER_HPP

#include <QDebug>
#include <arkhe/osgi/osgi.hpp>

class QVariant;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT ServiceTracker
		{

		public:
			ServiceTracker();
			virtual ~ServiceTracker();
		protected:

		private:

		};		
	}
}
#endif
