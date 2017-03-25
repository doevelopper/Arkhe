#ifndef ARKHE_OSGI_CORE_FRAMEWORK_PLUGINCONSTANTS_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_PLUGINCONSTANTS_HPP

#include <QString>
#include <arkhe/osgi/osgi.hpp>

class QVariant;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT PluginConstants
		{

		public:
			PluginConstants();
			virtual ~PluginConstants();

		protected:

		public:
			static const QString SYSTEM_PLUGIN_LOCATION;
			static const QString SYSTEM_PLUGIN_SYMBOLICNAME;
			static const QString FRAMEWORK_VERSION;
			static const QString FRAMEWORK_VENDOR;
			static const QString FRAMEWORK_STORAGE;
			static const QString FRAMEWORK_STORAGE_CLEAN;
			static const QString FRAMEWORK_STORAGE_CLEAN_ONFIRSTINIT;
			static const QString FRAMEWORK_PLUGIN_LOAD_HINTS;
			static const QString FRAMEWORK_PRELOAD_LIBRARIES;
			static const QString PLUGIN_SYMBOLICNAME;
			static const QString PLUGIN_COPYRIGHT;
			static const QString PLUGIN_DESCRIPTION;
			static const QString PLUGIN_NAME;
			static const QString PLUGIN_VENDOR;
			static const QString PLUGIN_LOCALIZATION;
			static const QString PLUGIN_LOCALIZATION_DEFAULT_BASENAME;
			static const QString REQUIRE_PLUGIN;
			static const QString PLUGIN_VERSION_ATTRIBUTE;
			static const QString PLUGIN_VERSION;
			static const QString PLUGIN_ACTIVATIONPOLICY;
			static const QString PLUGIN_UPDATELOCATION;
			static const QString ACTIVATION_EAGER;
			static const QString ACTIVATION_LAZY;
			static const QString RESOLUTION_DIRECTIVE;
			static const QString RESOLUTION_MANDATORY;
			static const QString RESOLUTION_OPTIONAL;
			static const QString OBJECTCLASS;
			static const QString SERVICE_ID;
			static const QString SERVICE_PID;
			static const QString SERVICE_RANKING;
			static const QString SERVICE_VENDOR;
			static const QString SERVICE_DESCRIPTION; 
		};
	}
}
#include <QLibrary>
#include <QMetaType>
Q_DECLARE_METATYPE(QLibrary::LoadHints)

#endif
