#include <arkhe/osgi/core/framework/ServiceEvent.hpp>

osgi::core::ServiceEvent::ServiceEvent()
: d(0)
{
}

osgi::core::ServiceEvent::~ServiceEvent()
{
}

osgi::core::ServiceEvent::ServiceEvent(Type type, const ServiceReference& reference)
  : d(new osgi::core::ServiceEventData(type, reference))
{

}

bool osgi::core::ServiceEvent::isNull() const
{
  return !d;
}

osgi::core::ServiceEvent::ServiceEvent(const ServiceEvent& other)
  : d(other.d)
{

}


osgi::core::ServiceEvent& osgi::core::ServiceEvent::operator=(const ServiceEvent& other)
{
	d = other.d;
	return *this;
}


osgi::core::ServiceReference ServiceEvent::getServiceReference() const
{
	return d->reference;
}


osgi::core::ServiceEvent::Type osgi::core::ServiceEvent::getType() const
{
	return d->type;
}

QDebug operator<<(QDebug dbg, osgi::core::ServiceEvent::Type type)
{
	switch(type)
	{
		case osgi::core::ServiceEvent::MODIFIED:          return dbg << "MODIFIED";
		case osgi::core::ServiceEvent::MODIFIED_ENDMATCH: return dbg << "MODIFIED_ENDMATCH";
		case osgi::core::ServiceEvent::REGISTERED:        return dbg << "REGISTERED";
		case osgi::core::ServiceEvent::UNREGISTERING:     return dbg << "UNREGISTERING";

		default: return dbg << "unknown service event type (" << static_cast<int>(type) << ")";
  }
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const osgi::core::ServiceEvent& event)
{
  if (event.isNull()) return dbg << "NONE";

  ServiceReference sr = event.getServiceReference();
  // Some events will not have a service reference
  qlonglong sid = sr.getProperty(PluginConstants::SERVICE_ID).toLongLong();
  QStringList classes = sr.getProperty(PluginConstants::OBJECTCLASS).toStringList();

  dbg.nospace() << event.getType() << " " << sid << " objectClass=" << classes;
  return dbg.maybeSpace();
}
