#ifndef ARKHE_OSGI_CORE_FRAMEWORK_PLUGIN_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_PLUGIN_HPP

#include <QHash>
#include <QWeakPointer>
#include <QMetaType>
#include <QUrl>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class PluginContext;
		class PluginArchive;
		class PluginFrameworkContext;
		class PluginPrivate;

		class ARKHE_CORE_PLUGIN_FW_EXPORT Plugin
		{

		public:
		  enum State 
		  {
			UNINSTALLED = 0x00000001,
			INSTALLED = 0x00000002,
			RESOLVED = 0x00000004,
			STARTING = 0x00000008,
			STOPPING = 0x00000010,
			ACTIVE = 0x00000020
		  };

			Plugin();
			virtual ~Plugin();
		protected:

		private:

		};		
	}
}
#endif
