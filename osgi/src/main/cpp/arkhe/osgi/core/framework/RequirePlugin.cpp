#include <arkhe/osgi/core/framework/RequirePlugin.hpp>
#include <arkhe/osgi/core/framework/PluginPrivate.hpp>

osgi::core::RequirePlugin::RequirePlugin()
{
}

osgi::core::RequirePlugin::~RequirePlugin()
{
}

osgi::core::RequirePlugin::RequirePlugin(PluginPrivate* requestor, const QString& name, const QString& res, const QString& range)
	: name(name)
	, resolution(res.isEmpty() ? PluginConstants::RESOLUTION_MANDATORY : res)
	, pluginRange(range.isEmpty() ? VersionRange::defaultVersionRange() : range)
{

  if (resolution != PluginConstants::RESOLUTION_MANDATORY &&
      resolution != PluginConstants::RESOLUTION_OPTIONAL )
  {
    QString what = QString("Invalid directive : '")
                   + PluginConstants::RESOLUTION_DIRECTIVE + ":=" + this->resolution
                   + "' in manifest header '"
                   + PluginConstants::REQUIRE_PLUGIN + ": " + this->name
                   + "' of plugin with id " + requestor->id
                   + " (" + requestor->symbolicName + ")"
                   + ". The value must be either '"
                   + PluginConstants::RESOLUTION_MANDATORY + "' or '"
                   + PluginConstants::RESOLUTION_OPTIONAL  + "'.";

		throw InvalidArgumentException(what);
    }


}

bool osgi::core::RequirePlugin::overlap(const RequirePlugin& rp) const
{
  if (resolution == PluginConstants::RESOLUTION_MANDATORY &&
      rp.resolution != PluginConstants::RESOLUTION_MANDATORY)
  {
    return false;
  }
  return pluginRange.withinRange(rp.pluginRange);

}