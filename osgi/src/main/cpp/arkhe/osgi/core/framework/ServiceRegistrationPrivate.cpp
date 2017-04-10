#include <arkhe/osgi/core/framework/ServiceRegistrationPrivate.hpp>

osgi::core::ServiceRegistrationPrivate::ServiceRegistrationPrivate()
{
}

osgi::core::ServiceRegistrationPrivate::ServiceRegistrationPrivate(PluginPrivate* plugin, QObject* service,  const osgi::Dictionary& props)
  : ref(1)
  , service(service)
  , plugin(plugin)
  , reference(this)
  , properties(props)
  , available(true)
  , unregistering(false)
  , propsLock()
{

}

osgi::core::ServiceRegistrationPrivate::~ServiceRegistrationPrivate()
{
}

bool osgi::core::ServiceRegistrationPrivate::isUsedByPlugin(QSharedPointer<Plugin> p)
{
	QHash<QSharedPointer<Plugin>, int> deps = dependents;
	return deps.contains(p);
}

QObject* osgi::core::ServiceRegistrationPrivate::getService()
{
	return service;
}
