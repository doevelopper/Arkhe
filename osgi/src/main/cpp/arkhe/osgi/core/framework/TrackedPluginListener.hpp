#ifndef ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDPLUGINLISTENER_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_TRACKEDPLUGINLISTENER_HPP

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
		class ARKHE_CORE_PLUGIN_FW_EXPORT TrackedPluginListener
		{

		public:
			TrackedPluginListener();
			virtual ~TrackedPluginListener();
		protected:

		private:

		};		
	}
}
#endif
