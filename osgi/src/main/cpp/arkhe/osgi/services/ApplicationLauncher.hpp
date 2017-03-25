#ifndef ARKHE_OSGI_SERVICES_APPLICATIONLAUNCHER_HPP
#define ARKHE_OSGI_SERVICES_APPLICATIONLAUNCHER_HPP

#include <QObject>

#include <arkhe/osgi/osgi.hpp>

class QVariant;
class Runnable;

/*!
 * @brief 
 * 
 */
namespace osgi
{
	namespace svc
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT ApplicationLauncher
		{

		public:
			ApplicationLauncher();
			virtual ~ApplicationLauncher();
			virtual void launch(Runnable* app, const QVariant& applicationContext) = 0;
			virtual void shutdown() = 0;
		protected:

		private:

		};		
	}
}
Q_DECLARE_INTERFACE(osgi::svc::ApplicationLauncher, "000.levitics.arkhe.service.ApplicationLauncher")

#endif
