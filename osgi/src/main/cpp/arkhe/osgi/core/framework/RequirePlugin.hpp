#ifndef ARKHE_OSGI_CORE_FRAMEWORK_REQUIREPLUGIN_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_REQUIREPLUGIN_HPP

#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class PluginPrivate;
		class RequirePlugin
		{

		public:
			RequirePlugin();
			RequirePlugin(PluginPrivate* requestor, const QString& name, const QString& res, const QString& range);
			virtual ~RequirePlugin();

			bool overlap(const RequirePlugin& rp) const;			
			const QString name;
			const QString resolution;
			const VersionRange pluginRange;
		protected:

		private:

		};		
	}
}
#endif
